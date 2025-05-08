/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/05/08 17:44:47 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

int	ft_isspace(char c)
{
	const char	*spaces;
	int			i;

	i = 0;
	spaces = " \t\n\r\f\v";
	while (spaces[i])
	{
		if (c == spaces[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	dtectorexport_ok(char *line)
{
	int		i;
	int		j;
	int		aux;
	char	*laline;

	laline = "export";
	aux = 0;
	j = 0;
	i = 0;
	while (laline[j] != '\0')
		j++;
	while (line[i] != '\0')
	{
		if (line[i] == laline[aux])
			aux++;
		i++;
	}
	if (aux == j)
		return (1);
	return (0);
}
