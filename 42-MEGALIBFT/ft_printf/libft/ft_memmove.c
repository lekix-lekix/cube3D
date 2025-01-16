/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:56:50 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/15 10:04:42 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (n == 0)
		return (dest);
	if (!dest && !src)
		return (NULL);
	if (src < dest && dest < src + n)
	{
		while (n != 0)
		{
			((char *)dest)[n -1] = ((char *)src)[n -1];
			n--;
		}
	}
	else
	{
		i = -1;
		while (++i < n)
			((char *)dest)[i] = ((char *)src)[i];
	}
	return (dest);
}

// int main()
// {
//     char    src[] = "lorem ipsum dolor sit amet";
//     char *dest = src + 1;
//     printf("dest ptr = %p\n", dest);
//     printf("dest = %s\n", dest);
//     printf("memmove return = %p\n", ft_memmove(dest, src, 8));
//     printf("dest ptr = %p\n", dest);
//     printf("dest = %s\n", dest);
//     printf("src = %s\n", src);
//     printf("src ptr = %p\n", src);
//     printf("---------\n");
//     char    src2[] = "lorem ipsum dolor sit amet";
//     char *dest2 = src2 + 1;
//     printf("dest2 ptr = %p\n", dest2);
//     printf("dest2 = %s\n", dest2);
//     printf("memmove return = %p\n", memmove(dest2, src2, 8));
//     printf("dest2 ptr = %p\n", dest2);
//     printf("dest2 = %s\n", dest2);
//     printf("src2 = %s\n", src2);
//     printf("src2 ptr = %p\n", src2);
// }