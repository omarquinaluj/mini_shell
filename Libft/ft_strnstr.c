/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:11:00 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/18 14:30:32 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	char	*l;
	size_t	i;
	size_t	j;

	b = (char *)big;
	l = (char *)little;
	i = 0;
	j = 0;
	if (*l == '\0')
		return (b);
	while (i < len && b[i])
	{
		j = 0;
		while (i + j < len && b[i + j] && l[j] && b[i + j] == l[j])
			j++;
		if (l[j] == '\0')
			return (&b[i]);
		i++;
	}
	return (NULL);
}
