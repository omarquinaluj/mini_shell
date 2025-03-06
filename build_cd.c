/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:06:19 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:06:22 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	builtin_cd(t_cmd *cmd, t_env **envs)
{
	char		*path;
	char		current[1024];

	path = get_path(cmd, envs);
	if (path && path[0] == '~')
		tilted_path(envs, &path);
	if (!path)
		return (0);
	if (path[0])
	{
		if (chdir(path) == -1)
		{
			error_invalid(path);
			return (free(path), EXIT_FAILURE);
		}
		if (getcwd(current, 1024))
			set_env(envs, "PWD", ft_strdup(current));
	}
	free(path);
	return (EXIT_SUCCESS);
}
