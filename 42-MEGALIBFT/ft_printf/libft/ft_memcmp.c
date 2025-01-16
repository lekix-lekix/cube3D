/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:26:19 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/10 16:37:01 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = -1;
	str1 = s1;
	str2 = s2;
	while (++i < n)
	{
		if (str1[i] > str2[i])
			return (10);
		if (str1[i] < str2[i])
			return (-1);
	}
	return (0);
}
