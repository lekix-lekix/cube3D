/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:38:19 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/27 17:12:07 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	lensrc;
	size_t	lendst;
	size_t	j;

	if ((!dest || !src) && n == 0)
		return (0);
	i = 0;
	lensrc = ft_strlen(src);
	lendst = ft_strlen(dest);
	j = lendst;
	if (n > 0 && (lendst < (n - 1)))
	{
		while (src[i] && (lendst + i) < (n - 1))
		{
			dest[j] = src[i];
			j++;
			i++;
		}
		dest[j] = '\0';
	}
	if (n <= lendst)
		return (lensrc + n);
	return (lendst + lensrc);
}

// int	main(void)
// {
// 	char	str[] = "";
// 	char	str2[] = "";
// 	printf("ma fonction : %zu \n", ft_strlcat(str, str2, 1));
// 	printf("la vraie fonction : %zu", strlcat(str, str2, 1));
// }
