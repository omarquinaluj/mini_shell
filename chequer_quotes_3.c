/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/24 09:05:41 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	writequotes_34(char *line)
{
	int	j;
	int	aux;

	j = 0;
	while (line[j] != '\0')
		j++;
	aux = 0;
	aux = aux_counterquotes_34_aux(line, j);
	return (aux);
}

int	aux_isvalid(char *line, int *position, int b)
{
	int	aux2;
	int	aux3;
	int	aux4;
	int	aux5;

	aux2 = position[b - 1];
	aux3 = position[b - 2];
	aux4 = 0;
	aux5 = 0;
	while (aux3 <= aux2)
	{
		if ((line[aux3] >= 32 && line[aux3] <= 33)
			|| (line[aux3] >= 35 && line[aux3] <= 126))
			aux4++;
		if ((line[aux3] >= 32 && line[aux3] <= 38)
			|| (line[aux3] >= 40 && line[aux3] <= 126))
			aux5++;
		aux3++;
	}
	if (aux4 == 0 || aux5 == 0)
		return (1);
	return (0);
}

int	is_valid(char *line, int *position, int aux)
{
	int	b;
	int	j;
	int	i;

	b = 0;
	while (b < aux)
	{
		i = position[b];
		if (b + 1 >= aux)
			return (0);
		j = position[b + 1];
		while (i < j)
		{
			if ((line[i] == ' ' || line[i] == '\t')
				|| (line[i] >= 9 && line[i] <= 13))
				return (1);
			i++;
		}
		b = b + 2;
	}
	if (aux_isvalid(line, position, b) == 1)
		return (1);
	return (0);
}

int	detectorecho(char *line, int i, int p)
{
	int		j;
	int		aux;
	char	*laline;

	laline = "echo";
	aux = 0;
	j = 0;
	while (laline[j] != '\0')
		j++;
	while (i < p)
	{
		if (line[i] == laline[aux])
			aux++;
		i++;
	}
	if (aux == j)
		return (1);
	return (0);
}

int	detectorecho_ok(char *line)
{
	int		i;
	int		j;
	int		aux;
	char	*laline;

	laline = "echo";
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
	if ((aux == j) || dtectorepwd_ok(line) || dtectoreunset_ok(line))
		return (1);
	return (0);
}
