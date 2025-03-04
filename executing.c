/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:20 by owmarqui          #+#    #+#             */
/*   Updated: 2025/02/28 09:49:29 by alexander        ###   ########.fr       */
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

void	ft_execute(t_cmd *current, char **envp, int infile, int outfile)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		ft_infile(current, infile);
		ft_outfile(current, outfile);
		if (execve(current->pth_cmd, current->cmd, envp) == -1)
			exit(0);
	}
}

int	ft_pipex(t_cmd *cmd, char **envp, int file)
{
	int	pipex[2];

	ft_pipe(pipex);
	ft_execute(cmd, envp, file, pipex[WRITE]);
	close(pipex[WRITE]);
	if (file != STDIN_FILENO)
		close(file);
	return (pipex[READ]);
}



void	ft_init_exec(t_cmd **cmds, t_env **env)
{
	t_cmd	*current;
	int		file;
	int		len;
	char	**envp;

	current = *cmds;
	len = count_cmd_nodes(*cmds);
	envp = format_env(*env);
	ft_check_exec(current, envp);
	//ft_init_heredoc(current, env); // apañetelas 
	file = STDIN_FILENO;
	while (current)
	{
		if (is_builtin(current))
			file = ft_builtin(current, env, len);
		if (!current->next)
			ft_execute(current, envp, file, STDOUT_FILENO);
		else
			file = ft_pipex(current, envp, file);
		current = current->next;
	}
	if (file != STDIN_FILENO)
		close(file);
	ft_wait_for_childs();
	ft_free_cmd(cmds, envp);
}
