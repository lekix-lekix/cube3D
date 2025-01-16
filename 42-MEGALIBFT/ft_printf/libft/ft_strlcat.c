/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:32:31 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/15 10:07:54 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	if (!dst && size == 0)
		return (src_len + size);
	dst_len = ft_strlen(dst);
	i = ft_strlen(dst);
	j = -1;
	if (size == 0 || dst_len >= size)
		return (src_len + size);
	while (src[++j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}
