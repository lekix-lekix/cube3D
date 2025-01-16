/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:13:11 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/23 15:18:40 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putnbr_unsigned(unsigned int nb, int *count)
{
	if (nb <= 9)
	{
		ft_putchar_fd(nb + '0', 1);
		*count += 1;
	}
	if (nb > 9)
	{
		putnbr_unsigned(nb / 10, count);
		ft_putchar_fd((nb % 10) + '0', 1);
		*count += 1;
	}
}

int	ft_putnbr_unsigned(unsigned int nb)
{
	int	count;

	count = 0;
	putnbr_unsigned(nb, &count);
	return (count);
}

void	ft_putnbr(int nb, int *count)
{
	long int	number;

	number = nb;
	if (number < 0)
	{
		ft_putchar_fd('-', 1);
		number = -number;
		*count += 1;
	}
	if (number >= 0 && number <= 9)
	{
		ft_putchar_fd(number + '0', 1);
		*count += 1;
	}
	if (number > 9)
	{
		ft_putnbr(number / 10, count);
		ft_putchar_fd(number % 10 + '0', 1);
		*count += 1;
	}
}
