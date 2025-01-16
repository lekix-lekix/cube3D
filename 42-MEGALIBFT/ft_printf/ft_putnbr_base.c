/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:36:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/28 17:01:01 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putnbr_base(unsigned int number, char *base, unsigned int base_len,
		int *count)
{
	if (number < base_len)
	{
		ft_putchar_fd(base[number], 1);
		*count += 1;
	}
	if (number >= base_len)
	{
		putnbr_base(number / base_len, base, base_len, count);
		ft_putchar_fd(base[number % base_len], 1);
		*count += 1;
	}
}

int	ft_putnbr_base(unsigned int number, char *base)
{
	int	base_len;
	int	count;

	count = 0;
	base_len = ft_strlen(base);
	putnbr_base(number, base, base_len, &count);
	return (count);
}

void	lu_putnbr_base(uintptr_t number, char *base, int base_len, int *count)
{
	if (number < (long unsigned int)base_len)
	{
		ft_putchar_fd(base[number], 1);
		*count += 1;
	}
	if (number >= (long unsigned int)base_len)
	{
		lu_putnbr_base(number / base_len, base, base_len, count);
		ft_putchar_fd(base[number % base_len], 1);
		*count += 1;
	}
}

int	ft_lu_putnbr_base(uintptr_t nbr, char *base)
{
	int	base_len;
	int	count;

	count = 0;
	base_len = ft_strlen(base);
	lu_putnbr_base(nbr, base, base_len, &count);
	return (count);
}
