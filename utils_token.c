/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:50:24 by alexander         #+#    #+#             */
/*   Updated: 2025/05/01 10:47:25 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	skip_spaces(char *line, size_t *i)
{
	size_t	len;

	len = ft_strlen(line);
	if (!line || !i)
		return ;
	while (*i < len && line[*i] && line[*i]
		&& (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	increase_token_index(size_t *count, size_t *i)
{
	(*count)++;
	(*i)++;
}

bool	special_char(char c)
{
	return (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || (c == '_')));
}
