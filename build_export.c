/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:07:37 by owmarqui          #+#    #+#             */
/*   Updated: 2025/05/08 13:39:08 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	error_identifier(char *identifier)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static void	copy_env_to_array(t_env *env, t_env **array)
{
	int	i;

	i = 0;
	while (env)
	{
		array[i++] = env;
		env = env->next;
	}
}

static int	compare_env(const void *a, const void *b)
{
	t_env	*env_a;
	t_env	*env_b;

	env_a = *(t_env **)a;
	env_b = *(t_env **)b;
	return (ft_strcmp(env_a->key, env_b->key));
}

void	export_no_args(t_env *env)
{
	int		count;
	t_env	**env_array;
	int		i;

	count = env_count(env);
	env_array = malloc(sizeof(t_env *) * count);
	if (!env_array)
		return ;
	copy_env_to_array(env, env_array);
	qsort(env_array, count, sizeof(t_env *), compare_env);
	i = 0;
	while (i < count)
	{
		write(1, "declare -x ", 11);
		write(1, env_array[i]->key, ft_strlen(env_array[i]->key));
		if (env_array[i]->value)
		{
			write(1, "=\"", 2);
			write(1, env_array[i]->value, ft_strlen(env_array[i]->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
	free(env_array);
}
