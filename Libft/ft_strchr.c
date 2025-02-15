/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:04:19 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/24 16:55:17 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}
/*
#include  <stdio.h>
#include  <string.h>
int	main()
{
	const char	*str = "Hola, mundo";
	char 		ch= 'Z';
	char	*result = ft_strchr(str, ch);

	if (result != NULL)
		printf(("'%c' se encontro posición: %ld\n"), ch, result - str);
	else
		 printf("El carácter '%c' no se encontró en la cadena.\n", ch);
}*/
