/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:08:27 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:08:29 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

static int	is_valid_identifier(const char *str)
{
	size_t	i;

	if (!str || !str[0] || ft_isdigit(str[0]) || str[0] == '$')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(t_cmd *cmd, t_env **envs)
{
	size_t	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			fprintf(stderr, "minishell: unset: `%s`: not a valid identifier\n",
				cmd->args[i]);
			i++;
			continue ;
		}
		if (!remove_env(envs, cmd->args[i]))
			return (0);
		i++;
	}
	return (EXIT_SUCCESS);
}
