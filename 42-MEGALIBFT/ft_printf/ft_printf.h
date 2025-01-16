/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:02:07 by kipouliq          #+#    #+#             */
/*   Updated: 2024/01/11 16:31:03 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

typedef int		(*t_fp_conversion)(void *);

int				ft_printf(const char *format, ...);
void			ft_skip_space(const char *str, int *count, int *i);
int				t_fp_conversion_check(char c);
void			ft_write_count(char c, int *count);
void			ft_putnbr(int nb, int *count);
int				ft_putnbr_unsigned(unsigned int nb);
int				ft_putnbr_base(unsigned int number, char *base);
int				ft_lu_putnbr_base(uintptr_t nbr, char *base);
int				ft_printstr(void *ptr);
int				ft_printptr(void *ptr);
int				ft_printchar(void *ptr);
int				ft_printpercent(void *ptr);
int				ft_printhex_lower(void *ptr);
int				ft_printhex_upper(void *ptr);
int				ft_printdecimal(void *ptr);
int				ft_print_unsigned(void *ptr);

t_fp_conversion	convert_format(int c);

#endif