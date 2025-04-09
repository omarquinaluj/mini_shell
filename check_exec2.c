/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:15:31 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/25 08:24:47 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	funtion_aux_check(t_cmd *current, char *aux, char **envp,
					t_shell *shell)
{
	free(aux);
	ft_breack_check(current, envp, shell);
}

void	ft_check_exec(t_cmd *current, char **envp, t_shell *shell)
{
	char	*aux;
	int		i;

	while (current)
	{
		aux = ft_calloc(sizeof(char), 1);
		if (!aux)
			return ;
		i = 0;
		while (current->args[i])
		{
			if ((current->args[i + 1]) && (current->args[i][0] == '<'
				|| current->args[i][0] == '>'))
				ft_break_redir(current, current->args, &i);
			else
			{
				aux = ft_strjoin_gnl(aux, current->args[i]);
				aux = ft_strjoin_gnl(aux, " ");
				i++;
			}
		}
		current->cmd = ft_split(aux, 32);
		funtion_aux_check(current, aux, envp, shell);
		current = current->next;
	}
}

int	is_spaces(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	control_cases(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		if (line[i] == '<' || line[i] == '>')
		{
			if (line[i + 1] == line[i])
				i += 2;
			else
				i++;
		}
		if (is_space(line[i]))
			i++;
		if (!is_spaces(line[i]) && line[i] != '<' && line[i] != '>')
			return (0);
	}
	return (1);
}

int	is_arrows(t_cmd *cmd)
{
	if (ft_strcmp(cmd->name_cmd, "<") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, ">") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "<<") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, ">>") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "<>") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "><") == 0)
		return (1);
	else
		return (0);
}
