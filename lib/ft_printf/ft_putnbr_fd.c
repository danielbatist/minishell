/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:05:53 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/22 12:40:12 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	num_long;
	int				count;

	count = 0;
	if (nb < 0)
	{
		count += ft_putchar_fd(('-'), fd);
		num_long = nb * -1;
	}
	else
		num_long = nb;
	if (num_long >= 10)
		count += ft_putnbr_fd(num_long / 10, fd);
	count += ft_putchar_fd((num_long % 10) + '0', fd);
	return (count);
}
