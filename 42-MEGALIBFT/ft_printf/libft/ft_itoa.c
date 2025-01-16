/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:35:23 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/14 18:28:01 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_nb_len(int nb)
{
	int	digits;

	if (nb == 0)
		return (1);
	digits = 0;
	if (nb < 0)
	{
		digits++;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb /= 10;
		digits++;
	}
	return (digits);
}

static void	ft_convert(char *str, long int nb, int *i)
{
	if (nb < 0)
	{
		str[*i] = '-';
		nb = -nb;
		*i += 1;
	}
	if (nb >= 0 && nb <= 9)
	{
		str[*i] = nb + '0';
		*i += 1;
	}
	if (nb > 9)
	{
		ft_convert(str, nb / 10, i);
		str[*i] = nb % 10 + '0';
		*i += 1;
	}
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			n_len;
	int			i;
	char		*str;

	nb = n;
	n_len = ft_find_nb_len(nb);
	str = malloc(sizeof(char) * (n_len + 1));
	if (!str)
		return (NULL);
	str = ft_memset(str, '\0', n_len + 1);
	if (!str)
		return (NULL);
	i = 0;
	ft_convert(str, nb, &i);
	return (str);
}
