/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:05:05 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/24 14:39:36 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	t_fp_conversion_check(char c)
{
	int		i;
	char	convert_set[10];

	i = -1;
	ft_strlcpy(convert_set, "cspdiuxX%", 10);
	while (convert_set[++i])
	{
		if (convert_set[i] == c)
			return (1);
	}
	return (0);
}

void	ft_write_count(char c, int *count)
{
	write(1, &c, 1);
	*count += 1;
}
