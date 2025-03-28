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


/*
void	main_signal(int signal)
{
	g_minishell.signal = signal;
	if (signal == SIGINT)
	{
		if (!g_minishell.child_running)
			write(1, "\n", 1);
		else
		{
			
			void	main_signal(int sig)
			write(1, "\n", 1);
			if (g_minishell.signal_heredoc == 0)  // Solo si NO estamos en heredoc
			rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();

		}
		set_env(&g_minishell.envs, "?",
			ft_itoa(128 + g_minishell.signal));
	}
}*/

void main_signal(int signal)
{
	g_sig = signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_eof(void)
{
	g_sig = -1;
}

// Manejador de la señal SIGINT en el proceso de heredoc
void sigint_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		rl_on_new_line();
		rl_replace_line("", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

// Función de inicialización de señales para el proceso principal
void sig_parent(void)
{
    signal(SIGINT, main_signal);  // Capturamos SIGINT
    signal(SIGQUIT, SIG_IGN);     // Ignoramos SIGQUIT para evitar que termine el programa
}
