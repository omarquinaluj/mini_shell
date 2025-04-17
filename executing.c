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

pid_t	ft_execute(t_cmd *current, char **envp, int infile, int outfile)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_infile(current, infile);
		ft_outfile(current, outfile);
		if (execve(current->pth_cmd, current->cmd, envp) == -1)
		{
			free(current->pth_cmd);
			exit(127);
		}
	}
	return (pid);
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

void	ft_init_exec(t_cmd **cmds, t_env **env, t_shell *shell)
{
	t_cmd	*current;
	t_exec	exec;
	int		len;
	char	**envp;

	current = *cmds;
	len = count_cmd_nodes(*cmds);
	envp = format_env(*env);
	ft_check_exec(current, envp, shell);
	ft_init_heredoc(current, env);
	exec = init_t_exec(len);
	signal(SIGINT, SIG_IGN);
	while (current)
	{
		if (is_builtin(current))
			exec.file = ft_builtin(current, env, len, shell);
		else if (!current->next)
			exec.pid[exec.i] = ft_execute(current, envp, exec.file, 1);
		else
			exec.file = ft_pipex(current, envp, exec.file, exec);
		current = current->next;
		exec.i++;
	}
	ft_wait_for_childs(exec, shell);
	ft_free_cmd(cmds, envp);
}
