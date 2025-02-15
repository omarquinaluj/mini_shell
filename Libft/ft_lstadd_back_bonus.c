/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:41:24 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/22 11:42:17 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temporal;

	if (new == NULL)
		return ;
	temporal = (*lst);
	if (*lst)
	{
		while (temporal->next != NULL)
			temporal = temporal->next;
		temporal->next = new;
	}
	if (!(*lst))
		*lst = new;
}
