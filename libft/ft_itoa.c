/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:53:36 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/24 18:56:44 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*if_zero(void)
{
	char	*tab;

	tab = malloc(2 * sizeof(char));
	if (!tab)
		return (NULL);
	tab[0] = '0';
	tab[1] = '\0';
	return (tab);
}

static int	len_n(long int n)
{
	int	len;

	if (n > 0)
		len = 0;
	else
	{
		len = 1;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			i;
	char		*tab;

	nb = n;
	i = len_n(nb);
	if (nb == 0)
		return (if_zero());
	tab = malloc((len_n(nb) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	if (nb < 0)
	{
		tab[0] = '-';
		nb *= -1;
	}
	tab[i] = '\0';
	i--;
	while (nb != 0)
	{
		tab[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (tab);
}

// #include <limits.h>

// int	main(void)
// {
// 	printf("%s", ft_itoa(INT_MAX));
// }