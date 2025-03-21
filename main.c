/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/15 12:45:54 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int g_sig = 0;

static	bool  false_funtion(char *promptt)
{
	if (promptt)
		free(promptt);
	write (1, "exit\n", 5);
	return (false);
}
/*
static bool interruption(char *promptt)
{
	if (promptt)
		free(promptt);
	g_minishell.heredoc = 0;  // Resetear la señal
	return true;
}*/

static	bool	readentry(t_env **envs, t_cmd **cmds)
{
	char	*line;
	char	**tokens;
	char	*promptt;

	*cmds = NULL;
	promptt = funtion_aux2();
	line = readline(promptt);
	
	if (!line)
		return (false_funtion(promptt));
	add_history(line);
	if (*line == '\0')
		return (funtion_my_free(promptt, line), true);
	tokens = tokenize(line, *envs, NULL);
	funtion_my_free(promptt, line);
	if (!tokens)
		return (set_env(envs, "?", ft_strdup("2")), true);
	*cmds = init_cmds(tokens);
	free_tokens(tokens);
	return (true);
}

static int	program(t_cmd **cmds, t_env **envs, t_shell shell)
{
	while (1)
	{
		sig_parent();
		if (!readentry(envs, cmds))
			break ;
		if (*cmds)
		{
			set_env(envs, "_", ft_strdup(last_cmd_arg(*cmds)));
			//printtokens(cmds);
			// retorne el exit status capaz que tenga que hacer parte o implementalos atraves de una estrcutura
			ft_init_exec(cmds, envs, shell);
		}
		if (g_sig > 0)
			shell.exit_status = 128 + g_sig;
		if (g_sig == SIGINT)
			shell.exit_status = 130; 
		set_env(envs, "?", ft_itoa(shell.exit_status));
		if (shell.force_exit /* || is_child_process(*cmds) */)
			return (free_cmds(*cmds), shell.exit_status);
		free_cmds(*cmds);
	}
	return (shell.exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	t_env	*tmp;
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.force_exit = false;
	//shell.signal = 0;
	shell.heredoc = false;
	shell.child_running = 0;
	shell.envs = init_envs(envp);
	shell.exit_status = program(&cmds, &shell.envs, shell);
	if (g_sig > 0)// vainas que no entiendo ya me podre a ver
		shell.exit_status = 128 + g_sig;
	rl_clear_history();
	while (shell.envs)
	{
		tmp = shell.envs;
		shell.envs = shell.envs->next;
		free_env(tmp);
	}
	return (shell.exit_status);
}


