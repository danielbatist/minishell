/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:05:53 by dbatista          #+#    #+#             */
/*   Updated: 2025/01/23 16:10:26 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{
	unsigned int	num_long;
	int				count;

	count = 0;
	if (nb < 0)
	{
		count += ft_putchar('-');
		num_long = nb * -1;
	}
	else
		num_long = nb;
	if (num_long >= 10)
		count += ft_putnbr(num_long / 10);
	count += ft_putchar((num_long % 10) + '0');
	return (count);
}
