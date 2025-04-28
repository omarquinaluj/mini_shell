/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/25 18:56:47 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	hay_entre_coma_bin(const char *p, char c, const char *esp)
{
	const char	*q;
	int			hay_espacio;

	q = p;
	while (*q == c)
		q++;
	esp = q;
	hay_espacio = 0;
	while (*esp == ' ')
	{
		hay_espacio = 1;
		esp++;
	}
	return (hay_espacio);
}

int	hay_espacio_entre_coma_y_bin(char *str, char c)
{
	const char	*p;
	const char	*esp;
	int			hay_espacio;

	p = str;
	esp = NULL;
	while (*p)
	{
		if (*p == c)
		{
			hay_espacio = hay_entre_coma_bin(p, c, esp);
			if (strncmp(esp, "bin/", 4) == 0)
				return (hay_espacio);
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
