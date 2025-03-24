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
    (void) signal;
    write(STDOUT_FILENO, "\n", 1);  // Escribimos nueva línea para que la salida sea más limpia

    if (g_sig == 0)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    
    g_sig = 0;  // Restablecemos g_sig después de procesar la señal
}

// Manejador de la señal SIGINT en el proceso de heredoc
void sigint_heredoc_handler(int sig)
{
    (void)sig;
    g_sig = 1;  // Indicamos que se recibió la señal SIGINT
    write(STDOUT_FILENO, "\n", 1); // Escribimos nueva línea
    // Aquí no necesitamos usar ioctl. La interrupción se maneja de forma sencilla.
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

// Función de inicialización de señales para el proceso principal
void sig_parent(void)
{
    signal(SIGINT, main_signal);  // Capturamos SIGINT
    signal(SIGQUIT, SIG_IGN);     // Ignoramos SIGQUIT para evitar que termine el programa
}

void	sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
