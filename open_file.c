/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:09:20 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:09:22 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	count_cmd_nodes(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

int	ft_open(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	return (fd);
}

int	ft_infile(t_cmd *ps, int std)
{
	if (ps->infile && ps->infile[0][0] == '<')
	{
		if (ps->infile && ps->infile[0][1] == '<'
			&& ps->infile[0][0] == '<')
			std = ft_open(ps->pth_hd, O_RDONLY);
		else
			std = ft_open(ps->infile[1], O_RDONLY);
		if (std == -1)
			return (-1);
		dup2(std, STDIN_FILENO);
		close(std);
	}
	else if (std != STDIN_FILENO)
	{
		dup2(std, STDIN_FILENO);
		close(std);
	}
	return (0);
}

int	ft_outfile(t_cmd *ps, int std, t_shell *shell)
{
	int file;
	if (ps->outfile && ps->outfile[0][0] == '>')
	{
		if (ft_validate_directory(ps->outfile[1], shell) == -1)
		{
			error_st(*ps->outfile, "No such file or directory", 1, shell);
            return (-1);
		}
		if (ps->outfile[0][1] == '>' && ps->outfile[0][0] == '>')
			file = ft_open(ps->outfile[1], O_WRONLY | O_CREAT | O_APPEND);
		else
			file = ft_open(ps->outfile[1], O_WRONLY | O_CREAT | O_TRUNC);
		if (file == -1)
			return (-1);
		dup2(file, STDOUT_FILENO);
		close(std);
	}
	else if (std != STDOUT_FILENO)
	{
		dup2(std, STDOUT_FILENO);
		close(std);
	}
	return (0);
}