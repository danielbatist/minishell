/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:23:13 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/22 11:46:51 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_selector_fd(const char *format, va_list args, int fd)
{
	int		c;

	c = 0;
	if (*format == '%')
		c += ft_putchar_fd('%', fd);
	else if (*format == 'c')
		c += ft_putchar_fd((char)va_arg(args, int), fd);
	else if (*format == 's')
		c += ft_putstr_fd(va_arg(args, char *), fd);
	else if (*format == 'p')
		c += ft_putptr_fd(va_arg(args, unsigned long), 0, fd);
	else if (*format == 'd' || *format == 'i')
		c += ft_putnbr_fd(va_arg(args, int), fd);
	else if (*format == 'u')
		c += ft_putnbr_u_fd(va_arg(args, unsigned int), fd);
	else if (*format == 'x')
		c += ft_putnbr_hex_low_fd(va_arg(args, unsigned int), fd);
	else if (*format == 'X')
		c += ft_putnbr_hex_up_fd(va_arg(args, unsigned int), fd);
	return (c);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start (args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_selector_fd(&format[i], args, fd);
		}
		else
		{
			write (fd, &format[i], 1);
			count += 1;
		}
		i++;
	}
	va_end(args);
	return (count);
}
