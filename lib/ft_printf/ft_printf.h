/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:28:04 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/22 11:40:44 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *str, int fd);
int		ft_putptr_fd(unsigned long nbr, int pre, int fd);
int		ft_putnbr_fd(int nb, int fd);
int		ft_putnbr_u_fd(unsigned int nb, int fd);
int		ft_putnbr_hex_low_fd(unsigned int nb, int fd);
int		ft_putnbr_hex_up_fd(unsigned int nb, int fd);
int		ft_printf_fd(int fd, const char *format, ...);

#endif