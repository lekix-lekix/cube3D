/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:09:34 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/15 19:19:36 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int to_find, size_t n)
{
	size_t	i;
	char	c;

	i = 0;
	c = to_find;
	while (i < n)
	{
		if (*(char *)(str + i) == c)
			return ((char *)str + i);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	printf("ma fonction : %s\n", (char *)ft_memchr("hello world", 119, 10));
// 	printf("vraie fonction : %s", (char *)memchr("hello world", 119, 10));
// }
