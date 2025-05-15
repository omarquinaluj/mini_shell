/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension2_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/15 12:20:46 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	funtion_return(int fd)
{
	perror("Error al asignar memoria");
	close(fd);
}

void	funtion_while(char *buffer, ssize_t	total_read)
{
	int	i;

	i = 0;
	while (i < total_read)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			return ;
		}
		i++;
	}
	return ;
}

char	*get_hostname(void)
{
	int		fd;
	ssize_t	buffer_size;
	char	*buffer;
	ssize_t	total_read;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (perror("Error al abrir /etc/hostname"), NULL);
	buffer_size = 64;
	buffer = (char *)malloc(buffer_size);
	if (!buffer)
		return (funtion_return(fd), NULL);
	total_read = 0;
	if (!read_hostname_file(fd, &buffer, &buffer_size, &total_read))
		return (NULL);
	buffer[total_read] = '\0';
	funtion_while(buffer, total_read);
	return (close(fd), buffer);
}

void	str_plus(char *result, char *str2, int len1, int len2)
{
	int	j;

	j = 0;
	while (j < len2)
	{
		result[len1 + j] = str2[j];
		j++;
	}
}

char	*concat_strings(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;
	char	*result;
	size_t	i;

	if (!str1 || !str2)
		return (NULL);
	len1 = strlen(str1);
	len2 = strlen(str2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = str1[i];
		i++;
	}
	str_plus(result, str2, len1, len2);
	result[len1 + len2] = '\0';
	return (result);
}
