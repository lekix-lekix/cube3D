/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:38:38 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/12 15:53:04 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		if (write(fd, s, ft_strlen(s)) < 0)
		{
			perror("write");
			return ;
		}
	}
	if (write(fd, "\n", 1) < 0)
		perror("write");
}

/*
int	main(void)
{
	ft_putendl_fd("bonjour", 1);
} */
