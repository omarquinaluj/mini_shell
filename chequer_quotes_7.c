/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/25 11:01:00 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

bool	comand_valid_aux(char *token, char *rute, char *comand)
{
	while (token)
	{
		strcpy(rute, token);
		strcat(rute, "/");
		strcat(rute, comand);
		if (access(rute, X_OK) == 0)
			return (true);
		token = strtok(NULL, ":");
	}
	return (false);
}

// Verifica si un string es un comand válido del sistema
bool	comand_valid_axu(const char *line, char c)
{
	char	comand[256];
	char	*token;
	char	*path;
	char	path_copy[1024];
	char	rute[512];

	if (!line)
		return (0);
	comand[255] = '\0';
	ft_sscanf(line, "%255s", comand);
	clean_quotes_aux(comand, c);
	if (strlen(comand) == 0)
		return (0);
	path = getenv("PATH");
	if (!path)
		return (0);
	strncpy(path_copy, path, sizeof(path_copy));
	path_copy[sizeof(path_copy) - 1] = '\0';
	token = strtok(path_copy, ":");
	if (comand_valid_aux(token, rute, comand))
		return (1);
	return (0);
}

int	obtenersizehastabinslash(const char *s, char c)
{
	int	i;
	int	solocomas;

	i = 0;
	solocomas = 1;
	while (s[i] != '\0')
	{
		if (strncmp(&s[i], "bin/", 4) == 0)
		{
			if (solocomas == 0)
			{
				return (4);
			}
			else
			{
				return (i + 4);
			}
		}
		if (s[i] != c && s[i] != ' ')
			solocomas = 0;
		i++;
	}
	return (0);
}

int	mi_strncmp(const char *s1, const char *s2, size_t n, char c)//cambio
{
	size_t	i;
	int		b;
	int		aux;

	i = 0;
	b = 0;
	aux = 0;
	while ((s1[i] == c || s1[i] == ' ') && s1[i] != '\0')
	{
		if (s1[i] != c && s1[i] != ' ')
			break ;
		i++;
	}
	n = n - 1;
	while (i <= n && s1[i] != '\0' && s2[b] != '\0')
	{
		if (s1[i] == s2[b])
			aux++;
		i++;
		b++;
	}
	if (aux == 4)
		return (1);
	return (0);
}

int	funtion_bin(char *line, char c)
{
	int	aux2;
	int	n;

	n = obtenersizehastabinslash(line, c);
	aux2 = mi_strncmp(line, "bin/", n, c);
	return (aux2);
}
