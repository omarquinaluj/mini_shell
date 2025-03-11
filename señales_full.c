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
	g_minishell.signal = signal;
	if (signal == SIGINT)
	{
		if (!g_minishell.child_running)
			write(1, "\n", 1);
		else if (!g_minishell.heredoc)
			write(1, "\n", 1);
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		set_env(&g_minishell.envs, "?",
			ft_itoa(128 + g_minishell.signal));
	}
}


// sacado de un repo para heredoc
void	sig_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_parent(void)
{
	signal(SIGINT, main_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_argument_with_equals(char *arg, t_env **envs)
{
	t_env	*new_node;

	new_node = create_new_env_node(arg);
	if (new_node)
		add_env_node(envs, new_node);
}

void	handle_argument_without_equals(char *arg, t_env **envs)
{
	t_env	*found_env;
	t_env	*new_node;

	found_env = find_env_node(envs, arg);
	if (!found_env)
	{
		new_node = create_new_env_node(arg);
		if (new_node)
			add_env_node(envs, new_node);
	}
}

t_env	*find_env_node(t_env **env, char *key)
{
	t_env	*tmp;
	size_t	key_len;

	tmp = *env;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, key_len) == 0
			&& tmp->key[key_len] == '\0')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_env_node(t_env **env, t_env *new_node)
{
	t_env	*tmp;
	size_t	new_node_key_len;

	tmp = *env;
	new_node_key_len = ft_strlen(new_node->key) + 1;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, new_node->key, new_node_key_len) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_node->value);
			free_env_node(new_node);
			return ;
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new_node;
}

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}

t_env	*sort_env_list(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		swapped;

	if (!env)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp1 = *env;
		while (tmp1->next != NULL)
		{
			tmp2 = tmp1->next;
			if (cmp_env_nodes(tmp1, tmp2))
			{
				swap_env_nodes(tmp1, tmp2);
				swapped = 1;
			}
			tmp1 = tmp1->next;
		}
	}
	return (*env);
}

int	cmp_env_nodes(t_env *tmp1, t_env *tmp2)
{
	size_t	max_length;

	if (ft_strlen(tmp1->key) > ft_strlen(tmp2->key))
		max_length = ft_strlen(tmp1->key);
	else
		max_length = ft_strlen(tmp2->key);
	if (ft_strncmp(tmp1->key, tmp2->key, max_length) > 0)
		return (1);
	else
		return (0);
}

void	swap_env_nodes(t_env *tmp1, t_env *tmp2)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = tmp1->key;
	tmp_value = tmp1->value;
	tmp1->key = tmp2->key;
	tmp1->value = tmp2->value;
	tmp2->key = tmp_key;
	tmp2->value = tmp_value;
}

t_env	*create_new_env_node(char *key_value)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(key_value, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		new_node->key = ft_strdup(key_value);
		new_node->value = ft_strdup(equal_sign + 1);
		*equal_sign = '=';
	}
	else
	{
		new_node->key = ft_strdup(key_value);
		new_node->value = ft_strdup("");
	}
	new_node->next = NULL;
	return (new_node);
}


void	error_numerical_arg2(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	verify_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][0] == '-' || args[i][0] == '+')
			j++;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (error_numerical_arg2(args[i]), 255);
			j++;
		}
		if (args[i + 1])
		{
			g_minishell.force_exit = false;
			return (error("exit", "too many arguments"), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
// vainas para joder  creo
bool	is_overflowing(const char *s)
{
	bool	is_negative;

	is_negative = false;
	if (s && *s == '-')
		is_negative = true;
	if (ft_strlen(s) - is_negative > 19)
		return (true);
	if (is_negative && ft_strcmp(s + 1, "9223372036854775808") > 0)
		return (true);
	else if (!is_negative && ft_strcmp(s, "9223372036854775807") > 0)
		return (true);
	return (false);
}

void	ft_echo_env_pwd(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->name_cmd, "echo") == 0)
		g_minishell.exit_status = builtin_echo(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "env") == 0)
		g_minishell.exit_status = builtin_env(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "pwd") == 0)
		g_minishell.exit_status = builtin_pwd(cmd, env);
	/* if(g_minishell.exit_status == EXIT_FAILURE) //si meten opt en lo comando los tira como bien
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->name_cmd, 2);
		ft_putstr_fd(" command not found\n", 2);
	} */
}

void	ft_cd_exit_export_unset(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->name_cmd, "cd") == 0)
		g_minishell.exit_status = builtin_cd(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "exit") == 0)
		g_minishell.exit_status = builtin_exit(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "export") == 0)
		g_minishell.exit_status = builtin_export(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "unset") == 0)
		g_minishell.exit_status = builtin_unset(cmd, env);
	/* if(g_minishell.exit_status == EXIT_FAILURE) //si meten opt en lo comando los tira como bien
	{
		perror(cmd->name_cmd);
	} */
}
