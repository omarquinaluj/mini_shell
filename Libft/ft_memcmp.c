/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:51:16 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/18 15:08:32 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int main() {
	char str1[] = "Hello";
	char str2[] = "Hellz";

	int result = ft_memcmp(str1, str2, 5);  // Comparar los primeros 5 bytes
	if (result == 0)
		printf("Los bloques de memoria son iguales.\n");
	else
		printf("Los bloques de memoria son diferentes: %d\n", result);
	return 0;
}*/
