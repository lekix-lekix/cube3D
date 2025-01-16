/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_calls_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:04:38 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/23 15:13:38 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printhex_lower_bis(void *ptr)
{
	int	*number;
	int	count;

	number = ptr;
	count = ft_putnbr_base(*number, "0123456789abcdef");
	return (count);
}

int	ft_printhex_lower(void *ptr)
{
	int	count;

	count = ft_printhex_lower_bis(&ptr);
	return (count);
}

int	ft_printhex_upper_bis(void *ptr)
{
	int	*number;
	int	count;

	number = ptr;
	count = ft_putnbr_base(*number, "0123456789ABCDEF");
	return (count);
}

int	ft_printhex_upper(void *ptr)
{
	int	count;

	count = ft_printhex_upper_bis(&ptr);
	return (count);
}
