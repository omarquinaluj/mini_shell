/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:19:21 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/18 13:50:32 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	size_t				i;

	p = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return ((void *)&p[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	buffer[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char	value = 'Z';
	char	*result = ft_memchr(buffer, value, sizeof(buffer));

	if (result != NULL)
		printf("El byte '%c'en la posición: %ld\n", value, result - buffer);
	else
		 printf("El byte '%c' no se encontró en le bloque memoria.\n", value);
	return (0);
}*/
