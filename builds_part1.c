/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builds_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:08:44 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:08:46 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_run_builtin(t_cmd *cmd, t_env **env, t_shell *shell)
{
	if (!cmd->name_cmd)
		return (1);
	if (ft_strcmp(cmd->name_cmd, "echo") == 0 || \
		ft_strcmp(cmd->name_cmd, "env") == 0 || \
		ft_strcmp(cmd->name_cmd, "pwd") == 0)
	{
		ft_echo_env_pwd(cmd, env, shell);
		return (shell->exit_status);
	}
	else if (ft_strcmp(cmd->name_cmd, "cd") == 0 || \
			ft_strcmp(cmd->name_cmd, "exit") == 0 || \
			ft_strcmp(cmd->name_cmd, "export") == 0 || \
			ft_strcmp(cmd->name_cmd, "unset") == 0)
	{
		ft_cd_exit_export_unset(cmd, env, shell);
		return (shell->exit_status);
	}
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	if (cmd->name_cmd == NULL)
		return (0);
	else if (ft_strcmp(cmd->name_cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "unset") == 0)
		return (1);
	return (0);
}
