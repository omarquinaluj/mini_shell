/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/29 10:16:32 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	get_int_quotes_and_bin(const char *p, char c, const char *esp)
{
	const char	*q;
	int			iss_space;

	q = p;
	while (*q == c)
		q++;
	esp = q;
	iss_space = 0;
	while (*esp == ' ')
	{
		iss_space = 1;
		esp++;
	}
	return (iss_space);
}

int	iss_space_in_quotes_bin(char *str, char c)
{
	const char	*p;
	const char	*esp;
	int			iss_space;

	p = str;
	esp = NULL;
	while (*p)
	{
		if (*p == c)
		{
			iss_space = get_int_quotes_and_bin(p, c, esp);
			if (ft_strncmp(esp, "bin/", 4) == 0)
				return (iss_space);
		}
		p++;
	}
	return (0);
}

int	isquotes(char *line)
{
	int	i;
	int	aux;

	i = 0;
	aux = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			aux = 1;
		if (line[i] == '"')
			aux = 2;
		i++;
	}
	return (aux);
}

int	isbin(char *line)
{
	int	aux2;
	int	aux3;

	aux3 = detected_quotes(line);
	if (aux3 == 0)
		return (0);
	if (isquotes(line) == 2)
	{
		aux2 = funtion_bin(line, '"');
		if (aux2 == 1)
			return (7);
	}
	if (isquotes(line) == 1)
	{
		aux2 = funtion_bin(line, '\'');
		if (aux2 == 1)
			return (7);
	}
	aux2 = funtion_bin(line, '\'');
	if (aux2 == 1)
		return (7);
	return (0);
}

int	funtio_dettorecho(char *line, t_shell *shell)
{
	if (detectorecho_ok(line) == 1)
	{
		if (funtion_quotes_echo(line, shell) == 1)
			return (1);
		else
			return (0);
	}
	return (0);
}
