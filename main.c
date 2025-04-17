/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/16 10:02:25 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

volatile sig_atomic_t	g_sig = 0;

static	bool	readentry(t_env **envs, t_cmd **cmds, t_shell *shell)
{
	char	*line;
	char	*promptt;
	char	*line2;
	int		aux;

	*cmds = NULL;
	line2 = NULL;
	promptt = funtion_aux2();
	line = readline(promptt);
	if (!line)
		return (false_funtion(promptt));
	add_history(line);
	if (*line == '\0')
		return (funtion_my_free(promptt, line), true);
	if (chequer_quotes(line, shell) == 1)
		return (funtion_my_free(promptt, line), true);
	aux = ft_compared(line);
	if (aux == 1)
	{
		line2 = ft_dup_line(line);
		if (!line2)
			free(line);
	}
	free (promptt);
	return (ft_readentry(line, line2, cmds, envs, shell));
}

static int	program(t_cmd **cmds, t_env **envs, t_shell *shell)
{
	sig_parent();
	while (1)
	{
		if (!readentry(envs, cmds, shell))
			break ;
		if (*cmds)
		{
			set_env(envs, "_", ft_strdup(last_cmd_arg(*cmds)));
			shell->exit_status = 0;
			ft_init_exec(cmds, envs, shell);
		}
		if (g_sig > 0)
			shell->exit_status = 128 + g_sig;
		if (g_sig == SIGINT)
			shell->exit_status = 130;
		set_env(envs, "?", ft_itoa(shell->exit_status));
		if (shell->force_exit)
			return (free_cmds(*cmds), shell->exit_status);
		free_cmds(*cmds);
	}
	return (shell->exit_status);
}

void	inicialize_struct(t_shell *shell, char **envp)
{
	t_cmd	*cmds;

	ft_bzero(shell, sizeof(t_shell));
	shell->exit_status = 0;
	shell->force_exit = false;
	shell->heredoc = false;
	shell->child_running = 0;
	shell->envs = init_envs(envp);
	shell->exit_status = program(&cmds, &shell->envs, shell);
}

void	free_shell(t_shell *shell)
{
	if (shell->envs)
	{
		free (shell->envs);
		shell->envs = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_env	*tmp;
	int		def_exit_status;

	inicialize_struct(&shell, envp);
	(void)argc;
	(void)argv;
	if (g_sig > 0)
		shell.exit_status = 128 + g_sig;
	rl_clear_history();
	while (shell.envs)
	{
		tmp = shell.envs;
		shell.envs = shell.envs->next;
		free_env(tmp);
	}
	def_exit_status = shell.exit_status;
	free_shell(&shell);
	return (def_exit_status);
}
