/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/14 08:39:24 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	detectedtour_quotes_1(char *line, int b, int aux)
{
	int	*counter_quotes;
	int	p;
	int	i;

	b = writequotes(line);
	counter_quotes = contquotes(line, b);
	if (!counter_quotes)
	{
		free(counter_quotes);
		return (0);
	}
	p = counter_quotes[1];
	i = counter_quotes[0];
	if (detectorecho(line, i, p) == 1)
	{
		while (i < p)
		{
			if (line[i] == ' ')
				aux++;
			i++;
		}
	}
	free (counter_quotes);
	return (aux);
}

int	detectedtour_quotes_2(char *line, int b, int aux)
{
	int	*counter_quotes;
	int	p;
	int	i;

	b = writequotes_34(line);
	counter_quotes = contquotes_34(line, b);
	if (!counter_quotes)
	{
		free(counter_quotes);
		return (0);
	}
	p = counter_quotes[1];
	i = counter_quotes[0];
	if (detectorecho(line, i, p) == 1)
	{
		while (i < p)
		{
			if (line[i] == ' ')
				aux++;
			i++;
		}
	}
	free(counter_quotes);
	return (aux);
}

int	funtion_quotes_echo(char *line, t_shell *shell)
{
	int	aux;
	int	b;

	aux = 0;
	b = 0;
	if (detectedtour_quotes(line) == 1)
	{
		aux = detectedtour_quotes_1(line, b, aux);
	}
	if (detectedtour_quotes(line) == 2)
	{
		aux = detectedtour_quotes_2(line, b, aux);
	}
	if (aux != 0)
	{
		error_stb("command not found", 127, shell);
		return (1);
	}
	else
		return (0);
}

int	aux_detector_1(char *line)
{
	int	b;
	int	*counter_quotes;

	b = writequotes(line);
	counter_quotes = contquotes(line, b);
	if (is_valid(line, counter_quotes, b) == 1)
	{
		return (free(counter_quotes), 1);
	}
	else
		return (free(counter_quotes), 0);
}

int	aux_detector_2(char *line)
{
	int	b;
	int	*counter_quotes;

	b = writequotes_34(line);
	counter_quotes = contquotes_34(line, b);
	if (is_valid(line, counter_quotes, b) == 1)
	{
		return (free(counter_quotes), 1);
	}
	else
		return (free(counter_quotes), 0);
}
