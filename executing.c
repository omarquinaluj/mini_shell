/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:20 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/20 10:54:04 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork");
	return (pid);
}

void	ft_pipe(int fd[2])
{
	int	p;

	p = pipe(fd);
	if (p < 0)
		perror("pipe");
}

int	ft_pipex(t_cmd *cmd, char **envp, int file, t_exec exec)
{
	int	pipex[2];

	ft_pipe(pipex);
	exec.pid[exec.i] = ft_execute(cmd, envp, file, pipex[WRITE]);
	close(pipex[WRITE]);
	if (file != STDIN_FILENO)
		close(file);
	return (pipex[READ]);
}

void	execution_loop(t_cmd *crt, t_shell *shell, t_exec *exec, char **envp)
{
	while (crt)
	{
		if (is_builtin(crt))
			exec->file = ft_builtin(crt, &shell->envs, exec->len, shell);
		else if (!crt->next)
		{
			exec->pid[exec->i] = ft_execute(crt, envp, exec->file, 1);
			exec->i++;
		}
		else
		{
			exec->file = ft_pipex(crt, envp, exec->file, *exec);
			exec->i++;
		}
		crt = crt->next;
	}
}

void	ft_init_exec(t_cmd **cmds, t_env **env, t_shell *shell)
{
	t_cmd	*current;
	t_exec	exec;
	char	**envp;

	current = *cmds;
	envp = format_env(*env);
	ft_check_exec(current, envp, shell);
	ft_init_heredoc(current, shell);
	exec = init_t_exec(*cmds);
	signal(SIGINT, SIG_IGN);
	execution_loop(current, shell, &exec, envp);
	ft_wait_for_childs(exec, shell);
	ft_free_cmd(cmds, envp);
}
