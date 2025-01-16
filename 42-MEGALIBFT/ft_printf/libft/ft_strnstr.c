/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:34:39 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/14 18:22:47 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!big && len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while ((big[i + j] == little[j]) && little[j])
			j++;
		if (little[j] == '\0' && i + j <= len)
			return ((char *)big + i);
		i++;
	}
	if (little[j] == '\0' && i + j <= len)
		return ((char *)big + i);
	return (NULL);
}

// #include <bsd/string.h>
// int main()
// {
//     printf("%s\n", ft_strnstr("aaabcabcd", "abc", 9));
//     printf("%s\n", strnstr("aaabcabcd", "abc", 9));
// }