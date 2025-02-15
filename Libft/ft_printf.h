/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:55 by owmarqui          #+#    #+#             */
/*   Updated: 2024/10/15 17:51:40 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define HEX_UPP_BASE "0123456789ABCDEF"
# define HEX_LOW_BASE "0123456789abcdef"

int		ft_printf(char const *str, ...);

void	ft_format(va_list va, char *str, size_t *counter);
void	ft_putchar_pf(char c, size_t *counter);
void	ft_putstr_pf(char *str, size_t *counter);
void	ft_putptr_pf(void *pr, size_t *counter);
void	ft_putnbr_pf(int num, size_t *counter);
void	ft_put_uns_int_pf(unsigned int num, size_t *counter);
void	ft_puthex_pf(unsigned int num, size_t *counter, char *base);

char	*ft_aux_pf(unsigned long long n, char *base);

#endif
