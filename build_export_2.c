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

int	handle_export_arg(char *arg, t_env **envs)
{
	size_t	j;

	if (arg[0] >= '0' && arg[0] <= '9')
		return (error_identifier(arg), EXIT_FAILURE);
	j = 0;
	while (arg[j] && arg[j] != '=')
	{
		if (special_char(arg[j]))
			return (error_identifier(arg), EXIT_FAILURE);
		j++;
	}
	if (j == 0)
		return (error_identifier(&arg[j]), EXIT_FAILURE);
	if (arg[j])
	{
		arg[j] = '\0';
		if (!set_env(envs, arg, ft_strdup(&arg[j + 1])))
			return (EXIT_FAILURE);
	}
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
