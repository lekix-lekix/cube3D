/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:02:37 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/27 17:13:10 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	if ((!big || !little) && n == 0)
		return (0);
	i = 0;
	j = 0;
	if (ft_strlen((char *)little) == 0)
		return ((char *)big);
	while (big[i] && i < n)
	{
		while ((big[i + j] == little[j]) && big[i + j] && (i + j) < n)
			j++;
		if (little[j] == '\0')
			return ((char *)big + (i));
		j = 0;
		i++;
	}
	return (0);
}

// int    main(void)
// {
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "abcd";
// 	printf("ma fonction : %s \n", ft_strnstr(haystack, needle, 9));
// }
