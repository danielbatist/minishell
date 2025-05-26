/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_triple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:34:34 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/25 22:36:23 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_triple(const char *s1, const char *s2, const char *s3)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	str = malloc((s1_len + s2_len + s3_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str, s2, s1_len + s2_len + 1);
	ft_strlcat(str, s3, s1_len + s2_len + s3_len + 1);
	return (str);
}
