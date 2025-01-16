/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:04:09 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/28 17:01:22 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_func_ptr(char c, void *curr_arg, int *count)
{
	t_fp_conversion	convert;

	convert = convert_format(c);
	*count += convert(curr_arg);
}

void	ft_str_parse(const char *str, va_list args, int *c_count)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			if (!t_fp_conversion_check(str[++i]) || !str[i])
			{
				if (!t_fp_conversion_check(str[i]) && !str[i])
				{
					*c_count = -1;
					return ;
				}
				ft_write_count(str[--i], c_count);
				continue ;
			}
			if (str[i] == '%')
				ft_func_ptr(str[i], NULL, c_count);
			else
				ft_func_ptr(str[i], va_arg(args, void *), c_count);
		}
		else
			ft_write_count(str[i], c_count);
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (format == NULL)
		return (-1);
	count = 0;
	va_start(args, format);
	ft_str_parse(format, args, &count);
	va_end(args);
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int res;

// 	res = ft_printf("%c, %s, %p, %d, %i, %u, %x, %X,
//	%%\n", 'a', "str", &res, 42, 42, -42, 1234, 1234);
// 	printf("res = %d\n", res);
// 	res = printf("%c, %s, %p, %d, %i, %u, %x, %X,
// %%\n", 'a', "str", &res, 42, 42, -42, 1234, 1234);
// 	printf("res = %d\n", res);
// 	ft_printf("%%%c%%%p%%%d%%%x\n", 'a', &res, 42, 12345);
// 	printf("res = %d\n", res);
// 	printf("%%%c%%%p%%%d%%%x\n", 'a', &res, 42, 12345);
// 	printf("res = %d\n", res);
// 	res = ft_printf(0);
// 	ft_printf("res = %d\n", res);
// 	res = ft_printf(0);
// 	printf("res = %d\n", res);
// }