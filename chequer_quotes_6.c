/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/25 11:00:45 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*dup_string(const char *origin)
{
	char	*neuw;
	size_t	lon;
	size_t	i;

	if (origin == NULL)
		return (NULL);
	lon = strlen(origin);
	neuw = (char *)malloc(lon + 1);
	if (neuw == NULL)
		return (NULL);
	i = 0;
	while (origin[i] != '\0')
	{
		neuw[i] = origin[i];
		i++;
	}
	neuw[i] = '\0';
	return (neuw);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*remaining;
	char		*init;

	remaining = NULL;
	if (str != NULL)
		remaining = dup_string(str);
	if (remaining == NULL || *remaining == '\0')
		return (NULL);
	while (*remaining != '\0')
	{
		if (*remaining == *delim)
			remaining++;
		else
			break ;
	}
	if (*remaining == '\0')
		return (NULL);
	init = remaining;
	aux_funtion(delim, remaining);
	if (*remaining == '\0')
		remaining = (NULL);
	return (init);
}

// Función que une todo: limpia el comand y revisa el argumento
int	line_valid(const char *line, char c)
{
	char		copy[256];
	char		*token;
	const char	*rest;

	if (!line)
		return (0);
	strncpy(copy, line, sizeof(copy));
	copy[sizeof(copy) - 1] = '\0';
	token = strtok(copy, " ");
	if (!token)
		return (0);
	clean_quotes(token);
	if (strlen(token) == 0)
		return (0);
	rest = strstr(line, " ");
	if (!rest)
		return (0);
	return (quotes_empty_or_spaces(rest, c));
}

void	clean_quotes_aux(char *str, char c)
{
	int		len;
	int		init;
	int		end;

	init = 0;
	len = strlen(str);
	while (str[init] == c && (init < len))
		init++;
	end = len - 1;
	while (end >= 0 && str[end] == c)
		end--;
	if (init > end)
	{
		str[0] = '\0';
		return ;
	}
	ft_memmove(str, str + init, end - init + 1);
	str[end - init + 1] = '\0';
}

int	ft_sscanf(const char *input, const char *format, char *output)
{
	int	max;
	int	i;
	int	j;

	max = 0;
	i = 0;
	j = 0;
	if (format[0] == '%' && format[strlen(format) - 1] == 's')
	{
		max = atoi(&format[1]);
		if (max <= 0)
			max = 255;
	}
	else
		return (0);
	while (ft_isspace(input[i]))
		i++;
	while (input[i] && !ft_isspace(input[i]) && j < max)
		output[j++] = input[i++];
	output[j] = '\0';
	if (j > 0)
		return (1);
	else
		return (0);
}
