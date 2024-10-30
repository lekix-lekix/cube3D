/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:38:50 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/27 17:08:31 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				n;
	unsigned char	ch;

	n = 0;
	while (str[n])
		n++;
	ch = c;
	while ((str[n] != ch) && (n > 0))
		n--;
	if (str[n] == ch)
		return ((char *)str + n);
	else
		return (0);
}

/*
// tests perso ok
int	main(void)
{
	printf("ma fonction : %s \n", ft_strrchr("", 105));
	printf("la vraie fonction : %s", strrchr("", 105));
}
*/