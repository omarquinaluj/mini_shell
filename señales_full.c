/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   señales_full.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:31:21 by alexander         #+#    #+#             */
/*   Updated: 2025/02/19 10:31:23 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	main_signal(int signal)
{
	g_sig = signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_heredoc_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

int	obtain_last_status(int *status)
{
	if (WTERMSIG(*status) != 0)
	{
		if (WTERMSIG(*status) == 3)
			ft_putstr_fd("Quit (core dumped)", 2);
		ft_putstr_fd("\n", 2);
		return (WTERMSIG(*status) + 128);
	}
	return (WEXITSTATUS(*status));
}

void	sig_parent(void)
{
	signal(SIGINT, main_signal);
	signal(SIGQUIT, SIG_IGN);
}
