/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:07:25 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/22 12:16:51 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_u_fd(unsigned int nb, int fd)
{
	int	count;

	count = 0;
	if (nb >= 10)
		count += ft_putnbr_fd((nb / 10), fd);
	count += ft_putchar_fd(((nb % 10) + '0'), fd);
	return (count);
}
