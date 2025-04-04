/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_low.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:54 by dbatista          #+#    #+#             */
/*   Updated: 2025/01/23 16:10:11 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex_low(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb > 15)
		count += ft_putnbr_hex_low(nb / 16);
	count += ft_putchar("0123456789abcdef"[nb % 16]);
	return (count);
}
