/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_readentry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:10:40 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:10:41 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

bool	is_invalid_redirection(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space((unsigned char)line[i]))
		i++;
	if (line[i] == '<' || line[i] == '>')
	{
		while (line[i] == '<' || line[i] == '>')
			i++;
		while (line[i] && is_space((unsigned char)line[i]))
			i++;
		if (line[i] == '\0')
			return (true);
	}
	return (false);
}
