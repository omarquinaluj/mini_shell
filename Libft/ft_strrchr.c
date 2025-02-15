/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:51:09 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/22 15:29:02 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == (char)c)
			return ((char *)&str[len]);
		len--;
	}
	return (NULL);
}
/*
#include  <stdio.h>
#include  <string.h>
int	main()
{
	const char	*str = "Hola, mundoa";
	char 		ch= 'a';
	char	*result = ft_strrchr(str, ch);

	if (result != NULL)
		printf(("'%c' se encontro posición: %ld\n"), ch, result - str);
	else
		 printf("El carácter '%c' no se encontró en la cadena.\n", ch);
}*/
