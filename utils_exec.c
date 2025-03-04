/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:42:29 by owmarqui          #+#    #+#             */
/*   Updated: 2025/02/15 18:42:31 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini_shell.h"

char	*ft_strjoin_gnl(char *stash, char *buff)
{
	char	*str;
	int		i;
	int		j;

	if (!stash || !buff)
		return (NULL);
	str = ft_calloc(sizeof(char), ft_strlen(stash) + ft_strlen(buff) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i])
	{
		str[i] = stash[i];
		i++;
	}
	j = 0;
	while (buff[j])
	{
		str[i + j] = buff[j];
		j++;
	}
	free(stash);
	return (str);
}

void	cmds_has_pipes(t_cmd *cmds)
{
	t_cmd	*head;

	head = cmds;
	while (head)
	{
		head->has_pipe = true;
		head = head->next;
	}
}
