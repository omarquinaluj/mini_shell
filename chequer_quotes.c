/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/13 11:39:11 by alexander        ###   ########.fr       */
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

int	chequer_quotes(char *line, t_shell *shell)
{
	int	b;

	if (detected_quotes(line) == 1 && detectorecho_ok(line) == 0)
	{
		if (detectedtour_quotes(line) == 1)
			b = aux_detector_1(line, shell);
		if (detectedtour_quotes(line) == 2)
			b = aux_detector_2(line, shell);
	}
	if (b == 1)
	{
		printf("command not found\n");
		return (1);
	}
	if (detectorecho_ok(line) == 1)
	{
		if (funtion_quotes_echo(line) == 1)
			return (shell->exit_status = 0, 1);
		else
			return (0);
	}
	return (0);
}
