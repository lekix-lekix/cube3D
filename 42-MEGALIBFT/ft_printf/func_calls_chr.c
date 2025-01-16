/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_calls_chr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:09:58 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/23 16:07:28 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_printstr(void *ptr)
{
	char	*str;
	char	str_null[7];
	int		i;

	i = 0;
	str = ptr;
	if (!str)
	{
		ft_strlcpy(str_null, "(null)", 7);
		ft_putstr_fd(str_null, 1);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printptr(void *ptr)
{
	uintptr_t	addr;
	int			count;
	char		str[6];

	addr = (uintptr_t)ptr;
	if (!addr)
	{
		ft_strlcpy(str, "(nil)", 6);
		ft_printstr(str);
		return (5);
	}
	write(1, "0x", 2);
	count = ft_lu_putnbr_base(addr, "0123456789abcdef");
	return (count + 2);
}

int	ft_printchar(void *ptr)
{
	char	*c;

	c = ptr;
	write(1, &c, 1);
	return (1);
}

int	ft_printpercent(void *ptr)
{
	(void)ptr;
	ft_putchar_fd('%', 1);
	return (1);
}
