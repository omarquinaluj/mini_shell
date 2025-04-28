/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/24 18:33:12 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	s = src;
	d = dest;
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (d > s)
	{
		i = 0;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	return (dest);
}

// Elimina comillas alrededor de un string
void	clean_quotes(char *str)
{
	size_t	len;

	len = strlen(str);
	while (str[0] == '"' && len > 0)
	{
		ft_memmove(str, str + 1, len);
		len--;
	}
	while (len > 0 && str[len - 1] == '"')
	{
		str[len - 1] = '\0';
		len--;
	}
}

int	ft_isspace(char c)
{
	const char	*spaces;
	int			i;

	i = 0;
	spaces = " \t\n\r\f\v";
	while (spaces[i])
	{
		if (c == spaces[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// Verifica si el argumento entre comillas está vacío o contiene solo spaces
bool	quotes_empty_or_spaces(const char *str, char c)
{
	const char	*fist_quote;
	const char	*second_quote;
	const char	*p;

	fist_quote = strchr(str, c);
	if (!fist_quote)
		return (0);
	second_quote = strchr(fist_quote + 1, c);
	if (!second_quote)
		return (0);
	if (strchr(second_quote + 1, c))
		return (0);
	p = fist_quote + 1;
	while (p < second_quote)
	{
		if (!ft_isspace((unsigned char)*p))
			return (0);
		p++;
	}
	return (1);
}

void	aux_funtion(const char *delim, char *remaining)
{
	while (*remaining != '\0')
	{
		if (*remaining == *delim)
		{
			*remaining = '\0';
			remaining++;
			break ;
		}
		remaining++;
	}
}
