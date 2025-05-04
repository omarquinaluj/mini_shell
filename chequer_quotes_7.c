/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/05/04 10:29:14 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

bool	comand_valid_aux(char *token, char *rute, char *comand)
{
	while (token)
	{
		ft_strcpy(rute, token);
		ft_strcat(rute, "/");
		ft_strcat(rute, comand);
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
	if (ft_strlen(comand) == 0)
		return (0);
	path = getenv("PATH");
	if (!path)
		return (0);
	ft_strncpy(path_copy, path, sizeof(path_copy));
	path_copy[sizeof(path_copy) - 1] = '\0';
	token = strtok(path_copy, ":");
	if (comand_valid_aux(token, rute, comand))
		return (1);
	return (0);
}

int	get_size_bin(const char *s, char c)
{
	int	i;
	int	onlyquotes;

	i = 0;
	onlyquotes = 1;
	while (s[i] != '\0')
	{
		if (ft_strncmp(&s[i], "/bin/", 5) == 0)
		{
			if (onlyquotes == 0)
			{
				return (5);
			}
			else
			{
				return (i + 5);
			}
		}
		if (s[i] != c && s[i] != ' ')
			onlyquotes = 0;
		i++;
	}
	return (0);
}

int	mi_strncmp(const char *s1, const char *s2, size_t n, char c)
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
	if (aux == 5)
		return (1);
	return (0);
}

int	funtion_bin(char *line, char c)
{
	int	aux2;
	int	n;

	n = get_size_bin(line, c);
	aux2 = mi_strncmp(line, "/bin/", n, c);
	return (aux2);
}
