/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:25:17 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/22 15:19:01 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size == 0 || size <= dest_len)
		return (size + src_len);
	while (src[i] && (dest_len + i) < size -1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

/*int	main(void)
{
	char dest[30] = "Hello, "; // Búfer con suficiente espacio
    char src[] = "world!";
    unsigned int size = sizeof(dest);
    unsigned int result;

    printf("Before ft_strlcat:\n");
    printf("dest: '%s'\n", dest);
    printf("src: '%s'\n", src);

    result = ft_strlcat(dest, src, size);

    printf("After ft_strlcat:\n");
    printf("dest: '%s'\n", dest);
    printf("Total length: %u\n", result);
    return 0;
}*/
