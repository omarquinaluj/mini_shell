/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:42:14 by owmarqui          #+#    #+#             */
/*   Updated: 2025/02/19 10:48:19 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// bienvenido a mi locura
bool	check_tokens(char **tokens, int i, t_shell *shell)
{
	while (tokens[i])
	{
		if (tokens[i][0] == '|' || tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (tokens[i + 1] && tokens[i][0] == tokens[i + 1][0])
				return (error_unexpected(tokens[i + 1], 1
						+ (tokens[i][0] == '<' || tokens[i][0] == '>'), shell),
						false);
			if (tokens[i][0] == '|' && (i == 0 || !tokens[i - 1]
					|| tokens[i - 1][0] == '|' || tokens[i - 1][0] == '>'
					|| tokens[i - 1][0] == '<'))
				return (error_unexpected("|", 1, shell), false);
			if ((tokens[i][0] == '<' || tokens[i][0] == '>') && !tokens[i + 1])
				return (true);
			if ((tokens[i][0] == '<' || tokens[i][0] == '>') && tokens[i + 1]
				&& (tokens[i + 1][0] == '<' || tokens[i + 1][0] == '>'))
				return (error_unexpected(tokens[i + 1], 1, shell), false);
		}
		i++;
	}
	return (true);
}

bool	check_newline(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' || tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (!tokens[i + 1] || (tokens[i][0] == '<'
				&& tokens[i + 1][0] == '>'))
				return (true);
		}
		i++;
	}
	return (true);
}

bool	handle_unexpected(char ***tokens, t_shell *shell)
{
	if (!check_tokens(*tokens, 0, shell))
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return (false);
	}
	if (!check_newline(*tokens))
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return (false);
	}
	return (true);
}
