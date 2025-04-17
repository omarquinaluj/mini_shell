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

void	update_exit_status_from_last(int status, t_shell *shell)
{
	int	exit_code;
	int	sig;

	sig = 0;
	exit_code = 0;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		shell->exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
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

	j = 0;
	while (j < exec.i)
	{
		waitpid(exec.pid[j], &status, 0);
		if (j == exec.i - 1)
			update_exit_status_from_last(status, shell);
		j++;
	}
	free(exec.pid);
	signal(SIGINT, main_signal);
}
