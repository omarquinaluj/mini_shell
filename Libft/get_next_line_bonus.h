/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:29:23 by owmarqui          #+#    #+#             */
/*   Updated: 2024/10/08 14:14:14 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FD 1024

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list2
{
	char			*str_buf;
	struct s_list2	*next;
}				t_list2;

void	append(t_list2 **list, char *buf);
int		len_to_newline(t_list2 *list);
void	copy_str(t_list2 *list, char *str);
t_list2	*find_last_node(t_list2 *list);
void	dealloc(t_list2 **list, t_list2 *clean_node, char *buff);
int		found_newline(t_list2 *list);
void	create_list(t_list2 **list, int fd);
char	*my_get_line(t_list2 *list);
void	list_strcat(t_list2 **list);
char	*get_next_line(int fd);

#endif
