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

t_minishell g_minishell;

static	bool  false_funtion(char *promptt)
{
	if (promptt)
		free(promptt);
	write(1, "exit\n", 5);
	return (false);
}

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

static int	program(t_cmd **cmds, t_env **envs)
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
			ft_init_exec(cmds, envs);
		}
		if (g_minishell.signal > 0)
			g_minishell.exit_status = 128 + g_minishell.signal;
		if (g_minishell.signal == SIGINT)
			g_minishell.exit_status = 130; 
		set_env(envs, "?", ft_itoa(g_minishell.exit_status));
		if (g_minishell.force_exit /* || is_child_process(*cmds) */)
			return (free_cmds(*cmds), g_minishell.exit_status);
		free_cmds(*cmds);
		g_minishell.signal = 0;
	}
	return (g_minishell.exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	t_env	*tmp;

	(void)argc;
	(void)argv;
	g_minishell.force_exit = false;
	g_minishell.signal = 0;
	g_minishell.heredoc = false;
	g_minishell.child_running = 0;
	g_minishell.envs = init_envs(envp);
	g_minishell.exit_status = program(&cmds, &g_minishell.envs);
	if (g_minishell.signal > 0)// vainas que no entiendo ya me podre a ver
		g_minishell.exit_status = 128 + g_minishell.signal;
	rl_clear_history();
	while (g_minishell.envs)
	{
		tmp = g_minishell.envs;
		g_minishell.envs = g_minishell.envs->next;
		free_env(tmp);
	}
	return (g_minishell.exit_status);
}


