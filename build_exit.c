/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:07:00 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:07:02 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	exit_arg(t_cmd *cmd, t_shell shell)
{
	long long	exit_code;
	t_env		*tmp;

	exit_code = ft_atoll(cmd->args[1]);
	free_cmds(cmd);
	while (shell.envs)
	{
		tmp = shell.envs;
		shell.envs = shell.envs->next;
		free_env(tmp);
	}
	exit(exit_code);
}

int	builtin_exit(t_cmd *cmd, t_env **envs, t_shell shell)
{
	int		verify_status;

	(void)envs;
	shell.force_exit = true;
	if (!cmd->has_pipe)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	verify_status = verify_args(cmd->args, shell);
	if (verify_status != EXIT_SUCCESS)
		return (verify_status);
	if (cmd->args[1] && is_overflowing(cmd->args[1]))
		return (error_numerical_arg2(cmd->args[1]), 255);
	if (cmd->args[1])
		exit_arg(cmd, shell);
	return (EXIT_SUCCESS);
}
