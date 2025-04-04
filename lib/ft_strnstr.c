/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:32:32 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/03 16:37:48 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*b;
	const char	*l;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (*big && i < len)
	{
		b = big;
		l = little;
		j = 0;
		while (*b && *l && *b == *l && i + j < len)
		{
			b++;
			l++;
			j++;
		}
		if (*l == '\0')
			return ((char *)big);
		big++;
		i++;
	}
	return (NULL);
}
