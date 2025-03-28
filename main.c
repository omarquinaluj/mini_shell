/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/27 12:22:40 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

volatile sig_atomic_t	g_sig = 0;

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

/*static	bool	readentry(t_env **envs, t_cmd **cmds)
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
}*/

char	*ft_dup_line(const char *str)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	while (*str == ' ')
		str++;
	new_str = malloc(strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
int	ft_compared(char *line)
{
	int	i;

	i = 0;
	if (line && line[0] == ' ')
	{
		while (line[i] != '\0')
		{
			if (line[i] == '<')
			{
				if (line[i++])
					return (1);
			}
			i++;
		}
	}
	return (0);
}


static	bool	readentry(t_env **envs, t_cmd **cmds)
{
	char	*line;
	char	**tokens;
	char	*promptt;
	char	*line2;
	int		aux;

	*cmds = NULL;
	tokens = NULL;
	promptt = funtion_aux2();
	line = readline(promptt);
	if (!line)
		return (false_funtion(promptt));
	add_history(line);
	if (*line == '\0')
		return (funtion_my_free(promptt, line), true);
	aux = ft_compared(line);
	if (aux == 1)
	{
		line2 = ft_dup_line(line);
		if (!line2)
			free(line);
		tokens = tokenize(line2, *envs, NULL);
	}
	else if (aux == 0)
		tokens = tokenize(line, *envs, NULL);
	funtion_my_free(promptt, line);
	if (aux == 1)
		free(line2);
	if (!tokens)
		return (set_env(envs, "?", ft_strdup("2")), true);
	*cmds = init_cmds(tokens);
	free_tokens(tokens);
	return (true);
}


static int	program(t_cmd **cmds, t_env **envs, t_shell *shell)
{
	sig_parent();
	while (1)
	{
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
			shell->exit_status = 128 + g_sig;
		//if (g_sig == SIGINT)
		//	shell->exit_status = 130; 

		set_env(envs, "?", ft_itoa(shell->exit_status));
		if (shell->force_exit /* || is_child_process(*cmds) */)
			return (free_cmds(*cmds), shell->exit_status);
		free_cmds(*cmds);
	}
	return (shell->exit_status);
}

void	inicialize_struct(t_shell *shell,char **envp)
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

void free_shell(t_shell *shell)
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
