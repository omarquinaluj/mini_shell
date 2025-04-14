/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension4_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/14 08:43:55 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

bool	false_funtion(char *promptt)
{
	if (promptt)
		free(promptt);
	write (1, "exit\n", 5);
	return (false);
}

//35 funtion_my_free(promptt, line);
bool	ft_readentry(char *line, char *line2,
			t_cmd **cmds, t_env **envs)
{
	char	**tokens;
	int		aux;

	aux = ft_compared(line);
	tokens = NULL;
	if (aux == 1)
		tokens = tokenize(line2, *envs, NULL);
	else if (aux == 0)
		tokens = tokenize(line, *envs, NULL);
	free (line);
	if (aux == 1)
		free(line2);
	if (!tokens)
		return (set_env(envs, "?", ft_strdup("2")), true);
	*cmds = init_cmds(tokens);
	free_tokens(tokens);
	return (true);
}
