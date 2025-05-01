/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/05/01 10:35:34 by alexander        ###   ########.fr       */
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
	lon = ft_strlen(origin);
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

int	line_valide(const char *line, char c)
{
	char		copi[256];
	char		*token;
	const char	*rest;

	strncpy(copi, line, sizeof(copi));
	copi[sizeof(copi) - 1] = '\0';
	token = strtok(copi, " ");
	if (!token)
		return (0);
	cleandd_quotes(token, c);
	if (strlen(token) == 0)
		return (0);
	rest = strstr(line, " ");
	if (!rest)
		return (0);
	return (quotes_empty_or_sapces(rest, c));
}

void	clean_quotes_aux(char *str, char c)
{
	int		len;
	int		init;
	int		end;

	init = 0;
	len = ft_strlen(str);
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
	if (format[0] == '%' && format[ft_strlen(format) - 1] == 's')
	{
		max = ft_atoi(&format[1]);
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
