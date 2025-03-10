/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:08:07 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:08:11 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	builtin_pwd(t_cmd *cmd, t_env **envs)
{
	char	path[1024];

	(void)envs;
	(void)cmd;
	if (!getcwd(path, 1024))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	if (!ft_putendl_fd(path, STDOUT_FILENO))
		return (error_write("pwd"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
