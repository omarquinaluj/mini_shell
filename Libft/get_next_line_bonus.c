/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:20:15 by owmarqui          #+#    #+#             */
/*   Updated: 2024/10/08 18:06:57 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

int	found_newline(t_list2 *list)
{
	int	i;

	if (!list)
		return (0);
	while (list != NULL)
	{
		i = 0;
		while (list->str_buf[i] && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	create_list(t_list2 **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(*list))
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buf);
			if (char_read < 0)
				dealloc(list, NULL, NULL);
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

char	*my_get_line(t_list2 *list)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = (char *)malloc(sizeof (char) * (str_len + 1));
	if (!next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	list_strcat(t_list2 **list)
{
	t_list2	*last_node;
	t_list2	*clean_node;
	int		i;
	int		k;
	char	*buf;

	if (!list)
		return ;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	clean_node = malloc(sizeof(t_list2));
	if (!buf || !clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_next_line(int fd)
{
	static t_list2	*fd_list[MAX_FD];
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
	{
		dealloc(&fd_list[fd], NULL, NULL);
		return (NULL);
	}
	create_list(&fd_list[fd], fd);
	if (!fd_list[fd])
		return (NULL);
	next_line = my_get_line(fd_list[fd]);
	list_strcat(&fd_list[fd]);
	return (next_line);
}
