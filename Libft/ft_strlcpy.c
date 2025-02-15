/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:07:57 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/22 15:26:03 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

/*int main(void) {
    char src[] = "Hello, world!";
    char dest[20]; // Buffer de destino suficientemente grande
    unsigned int copied_len;

    copied_len = ft_strlcpy(dest, src, sizeof(dest));
    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);
    printf("Length of source: %u\n", copied_len);

    // Probar con un tamaño de destino más pequeño
    char small_dest[6];
    copied_len = ft_strlcpy(small_dest, src, sizeof(small_dest));
    printf("\nSource: %s\n", src);
    printf("Small Destination: %s\n", small_dest);
    printf("Length of source: %u\n", copied_len);

    // Probar con tamaño 0
    char zero_dest[20];
    copied_len = ft_strlcpy(zero_dest, src, 0);
    printf("\nSource: %s\n", src);
    printf("Zero size Destination: %s\n", zero_dest);
    printf("Length of source: %u\n", copied_len);

    return 0;
}*/
