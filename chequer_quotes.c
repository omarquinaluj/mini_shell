/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/28 08:02:57 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	dtectoreunset_ok(char *line)
{
	int		i;
	int		j;
	int		aux;
	char	*laline;

	laline = "unset";
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

int	dtectorepwd_ok(char *line)
{
	int		i;
	int		j;
	int		aux;
	char	*laline;

	laline = "pwd";
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

int	funtion_nosuch_aux(char *line, int aux1, int b)
{
	aux1 = comand_valid_axu(line, '\'');
	if (aux1 == 0)
		b = 3;
	else
	{
		aux1 = line_valid(line, '\'');
		if (aux1 == 1)
			b = 5;
		else
			b = 4;
	}
	return (b);
}

int	funtion_nosuch(char *line)
{
	int	aux1;
	int	b;

	b = 0;
	if (isquotes(line) == 2)
	{
		aux1 = comand_valid_axu(line, '"');
		if (aux1 == 0)
			b = 3;
		else
		{
			aux1 = line_valid(line, '"');
			if (aux1 == 1)
				b = 5;
			else
				b = 4;
		}
	}
	if (isquotes(line) == 1)
		b = funtion_nosuch_aux(line, aux1, b);
	return (b);
}

int	chequer_quotes(char *line, t_shell *shell)
{
	int	b;
	int	aux2;

	b = 0;
	aux2 = isbin(line);
	if (detected_quotes(line) == 1 && detectorecho_ok(line) == 0 && aux2 == 0)
	{
		b = funtion_nosuch(line);
		if (detectedtour_quotes(line) == 1 && (b == 0 || b == 4))
			b = aux_detector_1(line);
		if (detectedtour_quotes(line) == 2 && (b == 0 || b == 4))
			b = aux_detector_2(line);
	}
	if (aux2 == 7)
		return (error_stb("no such file or directory", 127, shell), 1);
	if (b == 5)
		return (error_stb("no such file or directory", 127, shell), 1);
	if (b == 1)
		return (error_stb("comand not found", 127, shell), 1);
	if (funtio_dettorecho(line, shell))
		return (1);
	else
		return (0);
	return (0);
}
