/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:55:18 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/22 15:35:00 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*int main(void)
{
    char str1[] = "Hello, world!";
    char str2[] = "Hello, world!";
    char str3[] = "Hello, World!";
    char str4[] = "Hello, universe!";

    printf("'%s' and '%s' for 5: %d\n", str1, str2, ft_strncmp(str1, str2, 5));
    printf("'%s' and '%s' for 20: %d\n", str1, str2, ft_strncmp(str1, str2, 20));
    printf("'%s' and '%s' for 5: %d\n", str1, str3, ft_strncmp(str1, str3, 5));
    printf("'%s' and '%s' for 20: %d\n", str1, str3, ft_strncmp(str1, str3, 20));
    printf("'%s' and '%s' for 5: %d\n", str1, str4, ft_strncmp(str1, str4, 5));
    printf("'%s' and '%s' for 20: %d\n", str1, str4, ft_strncmp(str1, str4, 20));
    char empty[] = "";
    printf("'%s' and '%s' for 5: %d\n", str1, empty, ft_strncmp(str1, empty, 5));
    printf("'%s' and '%s' for 5: %d\n", empty, str1, ft_strncmp(empty, str1, 5));

    return 0;
}*/
