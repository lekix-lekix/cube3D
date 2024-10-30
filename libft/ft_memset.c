/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:43:11 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/08 15:31:17 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int x, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)str)[i] = (unsigned char)x;
		i++;
	}
	return (str);
}

/*
int	main(void)
{
	char *s = "Bonjour";
	void *p = &s;
	printf("ma fonction : %s \n", (char *)ft_memset(p, 'a', 4));
	printf("vraie fonction : %s", (char *)memset(p, 'a', 4));
} */