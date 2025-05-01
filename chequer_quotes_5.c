/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer_quotes_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:41:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/05/01 10:42:14 by alexander        ###   ########.fr       */
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

	len = strlen(str);
	while (str[0] == c && len > 0)
	{
		memmove(str, str + 1, len);
		len--;
	}
	while (len > 0 && str[len - 1] == c)
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

int	quotes_empty_or_sapces(const char *str, char c)
{
	const char	*p;
	int			have_quotes;

	p = str;
	have_quotes = 0;
	while (*p != '\0')
	{
		if (*p == c)
		{
			have_quotes = 1;
			p++;
			while (*p != c && *p != '\0')
			{
				if (!isspace((unsigned char)*p))
					return (0);
				p++;
			}
			if (*p != c)
				return (0);
			p++;
		}
		else if (isspace((unsigned char)*p))
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
