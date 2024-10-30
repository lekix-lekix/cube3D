/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:37:08 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/27 17:07:48 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbl;
	char		result;

	nbl = n;
	if (nbl < 0)
	{
		write(fd, "-", 1);
		nbl *= -1;
	}
	if (nbl >= 0 && nbl <= 9)
	{
		result = nbl + '0';
		write(fd, &result, 1);
	}
	if (nbl >= 10)
	{
		ft_putnbr_fd((nbl / 10), fd);
		ft_putnbr_fd((nbl % 10), fd);
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(2147483647, 1);
	return (0);
} */
