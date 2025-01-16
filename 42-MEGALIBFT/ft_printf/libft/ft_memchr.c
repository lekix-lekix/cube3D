/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:50:27 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/15 10:01:27 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		to_find;
	const unsigned char	*str;

	to_find = c;
	str = s;
	i = -1;
	while (++i < n)
	{
		if (str[i] == to_find)
			return ((void *)str + i);
	}
	return (NULL);
}
