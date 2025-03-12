/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:55:39 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/12 17:29:48 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_heredoc_write(char *ln, int file, t_env **envs)
{
	char	*var;
	int		start;
	int		j;

	j = 0;
	while (ln[j])
	{
		if (ln[j] == '$')
		{
			j++;
			start = j;
			while (ln[j] && ln[j] != 32 && ln[j] != '"' && ln[j] != '\'')
				j++;
			var = ft_substr(ln, start, (j - start));
			ft_putstr_fd(find_env_node(envs, var)->value, file);
		}
		else
			write(file, &ln[j++], 1);
	}
	write(file, "\n", 1);
}

void	ft_heredoc(t_cmd *current, int file, t_env **envs)
{
	char	*line;
	int		i;

	if (!current->dl_hd)
		perror("Error con el delimitador");
	i = 0;
	line = readline("> ");
	while (1)
	{
		if (ft_strncmp(line, current->dl_hd[i], ft_strlen(line) + 1) == 0)
			i++;
		if (!current->dl_hd[i])
			break ;
		if (!current->dl_hd[i + 1])
			ft_heredoc_write(line, file, envs);
		free(line);
		line = readline("> ");
	}
	free(line);
}

char	*ft_temp_name()
{
	char	*name;
	char	*num;
	int		i;

	i = 0;
	while (i != 2147483647)
	{
		num = ft_itoa(i);
		if(!num)
			return (NULL);
		name = ft_strjoin("/tmp/hd_", num);
		if(!name)
			return (NULL);
		free(num);
		if(access(name, F_OK) != 0)
			return(errno = 0, name);
		free(name);
		i++;
	}
	return (NULL);
}

void	ft_init_heredoc(t_cmd *current, t_env **envs)
{
	int	fd;
	//int	i;

	//i = 0;
	sig_heredoc();
	while (current)
	{
		if (current->infile && current->infile[0][1] == '<' && current->infile[0][0] == '<')
		{
			current->pth_hd = ft_temp_name();
			if (!current->pth_hd)
				perror("fallo con el temp name");
			fd = ft_open(current->pth_hd, O_WRONLY | O_CREAT | O_TRUNC);
			ft_heredoc(current, fd, envs);
			close(fd);
		}
		current = current->next;
	}
	//sig_parent();
}
