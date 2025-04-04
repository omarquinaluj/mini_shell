/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:59:14 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/24 16:59:16 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	error_numerical_arg2(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	verify_args(char **args, t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][0] == '-' || args[i][0] == '+')
			j++;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (error_numerical_arg2(args[i]), 255);
			j++;
		}
		if (args[i + 1])
		{
			shell->force_exit = false;
			return (error("exit", "too many arguments"), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	is_overflowing(const char *s)
{
	bool	is_negative;

	is_negative = false;
	if (s && *s == '-')
		is_negative = true;
	if (ft_strlen(s) - is_negative > 19)
		return (true);
	if (is_negative && ft_strcmp(s + 1, "9223372036854775808") > 0)
		return (true);
	else if (!is_negative && ft_strcmp(s, "9223372036854775807") > 0)
		return (true);
	return (false);
}

void	ft_echo_env_pwd(t_cmd *cmd, t_env **env, t_shell *shell)
{
	if (ft_strcmp(cmd->name_cmd, "echo") == 0)
		shell->exit_status = builtin_echo(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "env") == 0)
		shell->exit_status = builtin_env(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "pwd") == 0)
		shell->exit_status = builtin_pwd(cmd, env);
}

void	ft_cd_exit_export_unset(t_cmd *cmd, t_env **env, t_shell *shell)
{
	if (ft_strcmp(cmd->name_cmd, "cd") == 0)
		shell->exit_status = builtin_cd(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "exit") == 0)
		shell->exit_status = builtin_exit(cmd, env, shell);
	else if (ft_strcmp(cmd->name_cmd, "export") == 0)
		shell->exit_status = builtin_export(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "unset") == 0)
		shell->exit_status = builtin_unset(cmd, env);
}
