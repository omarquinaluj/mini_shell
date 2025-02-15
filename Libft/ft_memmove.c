/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:32:13 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/17 15:07:09 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (unsigned const char *)src;
	i = 0;
	if (!num || dest == src)
		return (dest);
	if (dest < src)
	{
		while (i < num)
		{
			d[i] = s[i];
			i++;
		}
		return (dest);
	}
	while (num--)
		d[num] = s[num];
	return (dest);
}
/*#include <stdio.h>
int main() {
    char str1[] = "1234567890";
    char str2[] = "1234567890";
    char str3[] = "1234567890";
    char str4[] = "1234567890";
    printf("Cadena original: %s\n", str1);
    // Prueba sin solapamiento (copiar a una región distinta)
    ft_memmove(str1 + 2, str1, 5);  // Copia "12345" a la posición 2
    printf("Resultado memmove sin solapamiento: %s\n", str1);
    // Prueba con solapamiento usando la función estándar para comparar
    ft_memmove(str4 + 5, str4, 5);  // Mueve "12345" a la posición 5 .
    printf("Resultado memmove estándar con solapamiento inverso: %s\n", str4);
    return 0;
}*/
