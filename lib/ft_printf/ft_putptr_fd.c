/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:02 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/22 12:17:08 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr_fd(unsigned long nbr, int pre, int fd)
{
	int	count;

	count = 0;
	if (nbr == 0)
	{
		return (ft_putstr_fd("(nil)", fd));
	}
	if (pre == 0)
		count += ft_putstr_fd("0x", fd);
	if (nbr > 15)
		count += ft_putptr_fd((nbr / 16), 1, fd);
	count += ft_putchar_fd("0123456789abcdef"[nbr % 16], fd);
	return (count);
}
