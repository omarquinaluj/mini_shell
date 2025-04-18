/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:10:28 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/20 22:10:30 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_exec	init_t_exec(t_cmd *cmds)
{
	t_exec	exec;
	int		len;

	len = count_cmd_nodes(cmds);
	exec.pid = malloc(sizeof(pid_t) * len);
	if (!exec.pid)
	{
		perror("error exec.pid");
		exit(1);
	}
	exec.len = len;
	exec.i = 0;
	exec.status = 0;
	exec.file = STDIN_FILENO;
	return (exec);
}
