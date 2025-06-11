/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_up_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:42 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/22 12:16:37 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex_up_fd(unsigned int nb, int fd)
{
	int	count;

	count = 0;
	if (nb >= 16)
		count += ft_putnbr_hex_up_fd((nb / 16), fd);
	count += ft_putchar_fd("0123456789ABCDEF"[nb % 16], fd);
	return (count);
}
