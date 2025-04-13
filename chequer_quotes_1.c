/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/13 11:22:48 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	detectedpared(int aux)
{
	if (aux % 2 == 0)
		return (1);
	else
		return (0);
}

int	detected_quotes(char *line)
{
	int	b;
	int	aux;

	aux = 0;
	b = 0;
	while (line[b] != '\0')
	{
		if (line[b] == '"' || line[b] == 39)
			aux++;
		b++;
	}
	if (aux == 0 || aux == 1 || detectedpared(aux) == 0)
		return (0);
	else
		return (1);
}

void	aux_counterquotes(char *line, int *counter_quotes, int j)
{
	int	i;
	int	aux;

	aux = 0;
	i = 0;
	while (i < j)
	{
		if (line[i] == 39)
		{
			counter_quotes[aux] = i;
			aux++;
			while (line[i] == 39 && i < j)
				i++;
			while ((line[i] >= 32 && line[i] <= 38)
				|| (line[i] >= 40 && line[i] <= 126 && i < j))
				i++;
			while (line[i] == 39 && i < j)
				i++;
			counter_quotes[aux] = i;
			aux++;
		}
		i++;
	}
	return ;
}

int	*contquotes(char *line, int aux)
{
	int	j;
	int	*counter_quotes;

	counter_quotes = malloc(aux * 4);
	j = 0;
	while (line[j] != '\0')
		j++;
	aux = 0;
	aux_counterquotes(line, counter_quotes, j);
	return (counter_quotes);
}

int	aux_counterquotes_aux(char *line, int j)
{
	int	i;
	int	aux;

	i = 0;
	aux = 0;
	while (i < j)
	{
		if (line[i] == 39)
		{
			aux++;
			while (line[i] == 39 && i < j)
				i++;
			while ((line[i] >= 32 && line[i] <= 38)
				|| (line[i] >= 40 && line[i] <= 126 && i < j))
				i++;
			while (line[i] == 39 && i < j)
				i++;
			aux++;
		}
		i++;
	}
	return (aux);
}
