/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaro-su <acaro-su@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/02 16:43:55 by acaro-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

volatile sig_atomic_t	g_sig = 0;

/*static	bool  false_funtion(char *promptt)
{
	if (promptt)
		free(promptt);
	write (1, "exit\n", 5);
	return (false);
}*/
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

/*bool	ft_readentry(char *line, char *line2, t_cmd **cmds, char *promptt, t_env **envs)
{
	char	**tokens;
	int		aux;

	aux = ft_compared(line);
	tokens = NULL;
	if (aux == 1)
		tokens = tokenize(line2, *envs, NULL);
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
}*/

//hola esto es un comentario

static	bool	readentry(t_env **envs, t_cmd **cmds)
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
	aux = ft_compared(line);
	if (aux == 1)
	{
		line2 = ft_dup_line(line);
		if (!line2)
			free(line);
	}
	return (ft_readentry(line, line2, cmds, promptt, envs));
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
			shell->exit_status = 0;
			// retorne el exit status capaz que tenga que hacer parte o implementalos atraves de una estrcutura
			ft_init_exec(cmds, envs, shell);
		}

		if (g_sig > 0)
			shell->exit_status = 128 + g_sig;
		if (g_sig == SIGINT)
			shell->exit_status = 130; 
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
