/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:24:58 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/25 12:34:09 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*aux;
	void	*aux_content;

	if (!lst || !f)
		return (NULL);
	aux_content = f(lst->content);
	if (!aux_content)
		return (NULL);
	aux = ft_lstnew(aux_content);
	if (!aux)
	{
		del(aux_content);
		return (NULL);
	}
	if (lst->next)
	{
		aux->next = ft_lstmap(lst->next, f, del);
		if (!aux->next)
		{
			ft_lstdelone(aux, del);
			return (NULL);
		}
	}
	return (aux);
}
//lst->next->next->content;
