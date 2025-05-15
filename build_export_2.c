/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:39:33 by alexander         #+#    #+#             */
/*   Updated: 2025/05/08 13:39:49 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	is_valid_identifier(const char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	handle_export_arg(char *arg, t_env **envs)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	if (!is_valid_identifier(arg))
		return (error_identifier(arg), EXIT_FAILURE);
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (EXIT_SUCCESS);
	key = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	if (!key || !value)
		return (free(key), free(value), EXIT_FAILURE);
	if (!set_env(envs, key, value))
		return (free(key), free(value), EXIT_FAILURE);
	free(key);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_cmd *cmd, t_env **envs)
{
	size_t	i;

	if (!cmd->args[1])
		return (export_no_args(*envs), EXIT_SUCCESS);
	i = 1;
	while (cmd->args && cmd->args[i])
	{
		if (handle_export_arg(cmd->args[i], envs) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
