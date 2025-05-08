/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:15:31 by owmarqui          #+#    #+#             */
/*   Updated: 2025/05/08 17:45:37 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_path_2(char **envp)
{
	int	i;

	if (!envp)
		return (-1);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	auxiliar_check_path(char **env_path, t_cmd *current)
{
	char	*path;
	char	*path_cmd;
	int		i;

	i = -1;
	while (env_path[++i])
	{
		path = ft_strjoin(env_path[i], "/");
		if (!path)
			continue ;
		path_cmd = ft_strjoin(path, current->cmd[0]);
		free(path);
		if (!path_cmd)
			continue ;
		if (access(path_cmd, X_OK) == 0)
		{
			current->pth_cmd = ft_strdup(path_cmd);
			free(path_cmd);
			return (0);
		}
		free(path_cmd);
	}
	return (1);
}

int	ft_check_path(t_cmd *current, char **envp)
{
	int		result;
	int		i;
	char	**env_path;

	i = ft_path_2(envp);
	if (i == -1 || !envp[i] || !envp[i][5])
		return (1);
	env_path = ft_split(envp[i] + 5, ':');
	if (!env_path)
		return (1);
	result = auxiliar_check_path(env_path, current);
	ft_free_double(env_path);
	return (result);
}
