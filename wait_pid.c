/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:11:57 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/17 18:11:59 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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

void	update_exit_status_from_last(int status, t_shell *shell, int exit_code)
{
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (shell->exit_status == 127)
			shell->exit_status = exit_code;
	}
}

void	ft_wait_for_childs(t_exec exec, t_shell *shell)
{
	int	j;
	int	status;
	int	sig;
	int	exit_code;

	exit_code = 0;
	sig = 0;
	j = 0;
	while (j < exec.i)
	{
		waitpid(exec.pid[j], &status, 0);
		exit_code = obtain_last_status(&status);
		shell->exit_status = exit_code;
		if (j == exec.i - 1 && exec.i >= 2)
			update_exit_status_from_last(status, shell, exit_code);
		j++;
	}
	free(exec.pid);
	signal(SIGINT, main_signal);
}
