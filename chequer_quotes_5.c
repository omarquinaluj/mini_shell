/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/05/01 11:29:05 by alexander        ###   ########.fr       */
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

void	cleandd_quotes(char *str, char c)
{
	size_t	len;

	len = ft_strlen(str);
	while (str[0] == c && len > 0)
	{
		ft_memmove(str, str + 1, len);
		len--;
	}
	while (len > 0 && str[len - 1] == c)
	{
		str[len - 1] = '\0';
		len--;
	}
}

int	while_funtion(const char **p, char c)
{
	(*p)++;
	while (**p && **p != c)
	{
		if (!ft_isspace((unsigned char)**p))
			return (0);
		(*p)++;
	}
	if (**p != c)
		return (0);
	(*p)++;
	return (1);
}

// Verifica si hay pares de comillas válidos con solo espacios entre ellas
int	quotes_empty_or_sapcess(const char *str, char c)
{
	const char	*p;
	int			have_quotes;

	have_quotes = 0;
	p = str;
	while (*p != '\0')
	{
		if (*p == c)
		{
			have_quotes = 1;
			if (!while_funtion(&p, c))
				return (0);
		}
		else if (ft_isspace((unsigned char)*p))
			p++;
		else
			return (0);
	}
	return (have_quotes);
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
