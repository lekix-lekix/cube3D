/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_calls_nb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:10:02 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/23 15:18:15 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printdecimal_bis(void *ptr)
{
	int	*number;
	int	count;

	count = 0;
	number = ptr;
	ft_putnbr(*number, &count);
	return (count);
}

int	ft_printdecimal(void *ptr)
{
	int	count;

	count = ft_printdecimal_bis(&ptr);
	return (count);
}

int	ft_print_unsigned_bis(void *ptr)
{
	unsigned int	*number;
	int				count;

	number = ptr;
	count = ft_putnbr_unsigned(*number);
	return (count);
}

int	ft_print_unsigned(void *ptr)
{
	int	count;

	count = ft_print_unsigned_bis(&ptr);
	return (count);
}
