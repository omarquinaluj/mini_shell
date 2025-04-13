/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/13 11:21:55 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	writequotes(char *line)
{
	int	j;
	int	aux;

	j = 0;
	while (line[j] != '\0')
		j++;
	aux = 0;
	aux = aux_counterquotes_aux(line, j);
	return (aux);
}

int	detectedtour_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			return (2);
		if (line[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

void	aux_counterquotes_34(char *line, int *counter_quotes, int j)
{
	int	i;
	int	aux;

	i = 0;
	aux = 0;
	while (i < j)
	{
		if (line[i] == 34)
		{
			counter_quotes[aux] = i;
			aux++;
			while (line[i] == 34 && i < j)
				i++;
			while ((line[i] >= 32 && line[i] <= 33)
				|| (line[i] >= 35 && line[i] <= 126 && i < j))
				i++;
			while (line[i] == 34 && i < j)
				i++;
			counter_quotes[aux] = i;
			aux++;
		}
		i++;
	}
	return ;
}

int	*contquotes_34(char *line, int aux)
{
	int	j;
	int	*counter_quotes;

	counter_quotes = malloc(aux * 4);
	j = 0;
	while (line[j] != '\0')
		j++;
	aux = 0;
	aux_counterquotes_34(line, counter_quotes, j);
	return (counter_quotes);
}

int	aux_counterquotes_34_aux(char *line, int j)
{
	int	aux;
	int	i;

	i = 0;
	aux = 0;
	while (i < j)
	{
		if (line[i] == 34)
		{
			aux++;
			while (line[i] == 34 && i < j)
				i++;
			while ((line[i] >= 32 && line[i] <= 33)
				|| (line[i] >= 35 && line[i] <= 126 && i < j))
				i++;
			while (line[i] == 34 && i < j)
				i++;
			aux++;
		}
		i++;
	}
	return (aux);
}
