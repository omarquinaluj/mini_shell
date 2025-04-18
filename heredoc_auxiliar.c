/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_auxiliar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:31:47 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/09 17:31:49 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	auxiliar_heredoc(char **line, t_cmd *current, int file, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	*line = readline("> ");
	while (*line)
	{
		if (!*line)
		{
			break ;
		}
		if (line && current->dl_hd[0]
			&& ft_strncmp(*line, current->dl_hd[0],
				ft_strlen(current->dl_hd[0]) + 1) == 0)
			break ;
		ft_heredoc_write(*line, file, &shell->envs);
		free (*line);
		*line = readline("> ");
	}
	free (*line);
	exit(0);
}

void	auxiliar_heredoc_write(int *j, int *start, char *line)
{
	(*j)++;
	*start = *j;
	while (line[*j] && line[*j] != ' '
		&& line[*j] != '"' && line[*j] != '\'')
		(*j)++;
}
