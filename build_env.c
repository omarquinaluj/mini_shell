/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:06:47 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:06:49 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

bool	is_special_env(char *key)
{
	char	*specials[1];
	size_t	i;

	specials[0] = "?";
	i = 0;
	while (i < 1)
	{
		if (!ft_strcmp(specials[i], key))
			return (true);
		i++;
	}
	return (false);
}

int	builtin_env(t_cmd *cmd, t_env **envs)
{
	t_env	*env;

	(void)cmd;
	env = *envs;
	while (env)
	{
		if (!is_special_env(env->key) && env->value)
		{
			if (!ft_putstr_fd(env->key, STDOUT_FILENO)
				|| !ft_putstr_fd("=", STDOUT_FILENO)
				|| !ft_putendl_fd(env->value, STDOUT_FILENO))
				return (error_write("env"), EXIT_FAILURE);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
