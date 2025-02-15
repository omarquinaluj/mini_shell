/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:12 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/22 17:29:34 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	digit_counter(int n)
{
	int	i;
	int	copy;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	copy = n;
	while (copy > 0)
	{
		copy = copy / 10;
		i++;
	}
	return (i);
}

int	number_exp(int n)
{
	int	exp;
	int	digits;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (1000000000);
	digits = digit_counter(n);
	if (n < 0)
		digits--;
	exp = 1;
	while (--digits)
		exp = exp * 10;
	return (exp);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			exp;
	int			i;
	long int	copy;

	copy = (long int)n;
	exp = number_exp(n);
	i = 0;
	str = malloc(digit_counter(n) + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[i++] = '-';
		copy = -copy;
	}
	while (exp > 0)
	{
		str[i++] = (copy / exp) + '0';
		copy = copy % exp;
		exp = exp / 10;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
int main()
{
    printf("1234 en base 10 es: %s\n", ft_itoa(1234));
    printf("-1234 en base 10 es: %s\n", ft_itoa(-1234));
    return (0);
}*/
