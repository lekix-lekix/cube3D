/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:39:27 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/21 18:31:51 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n > 0)
	{
		while (src[i] && i < (n - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

// int main()
// {
//     char d[14];
//     char s[10] = "0123456789";

//     char t[14];
//     char r[10] = "0123456789";
// 	size_t	p = 15;

//     ft_strlcpy(d, s, 15);
//     printf("ma dest = %s \n", d);
//     printf("ma fonction : %zu \n", ft_strlcpy(d, s, p));

//     strlcpy(t, r, 15);
//     printf("la vraie dest = %s \n", t);
//     printf("la vraie : %zu \n", strlcpy(t, r, p));
// }