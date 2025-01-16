/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:53:50 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/23 16:22:36 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fp_conversion	convert_format(int c)
{
	t_fp_conversion	*storage;

	storage = (t_fp_conversion[128]){
	['c'] = ft_printchar,
	['s'] = ft_printstr,
	['p'] = ft_printptr,
	['d'] = ft_printdecimal,
	['i'] = ft_printdecimal,
	['u'] = ft_print_unsigned,
	['x'] = ft_printhex_lower,
	['X'] = ft_printhex_upper,
	['%'] = ft_printpercent};
	return (storage[c]);
}
