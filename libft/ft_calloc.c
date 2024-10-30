/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:33:58 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/24 19:27:35 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*tab;

	if (nitems * size > 65535
		|| (nitems > 65535 && size > 65535))
		return (0);
	tab = malloc(nitems * size);
	if (!tab)
		return (0);
	ft_bzero(tab, (size * nitems));
	return (tab);
}

// int	main(void)
// {
// 	printf("ma fonction : %s \n", (char *)ft_calloc(5, sizeof(char)));
// 	printf("vraie fonction : %s", (char *)calloc(5, sizeof(char)));
// }
