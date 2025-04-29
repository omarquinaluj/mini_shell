/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:47:23 by alexander         #+#    #+#             */
/*   Updated: 2025/04/29 10:12:43 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

size_t	count_envs(t_env *envs)
{
	size_t	i;
	t_env	*tmp;

	i = 0;
	tmp = envs;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**format_env(t_env *envs)
{
	size_t	i;
	t_env	*tmp;
	char	*key;
	char	**output;

	i = count_envs(envs);
	output = malloc(sizeof(char *) * (i + 1));
	if (!output)
		return (NULL);
	i = 0;
	tmp = envs;
	while (tmp)
	{
		key = ft_strjoin(tmp->key, "=");
		output[i] = ft_strjoin(key, tmp->value);
		free(key);
		i++;
		tmp = tmp->next;
	}
	output[i] = NULL;
	return (output);
}

int	ft_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	perror("There is no PATH defined in the enviroment\n");
	return (i);
}
