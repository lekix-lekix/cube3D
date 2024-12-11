/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:06 by inbennou          #+#    #+#             */
/*   Updated: 2024/12/11 17:58:31 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	only_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_number(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	pos_atoi(char *str)
{
	int			i;
	long int	result;

	i = 0;
	result = 0;
	if (str[i] == '+' && ft_strlen(str) != 1)
		i++;
	if (!only_numbers(str + i) || ft_strlen(str) > 11 || ft_strlen(str) == 0)
		return (-1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (result >= 2147483647)
		return (-1);
	return (result);
}

double	wrap_angle_360(double angle, double change, bool add)
{
	double	angle_wrap;

	if (add)
	{
		angle_wrap = angle + change;
		if (angle_wrap > 360)
			angle_wrap = fmod(angle_wrap, 360);
	}
	else
	{
		angle_wrap = angle - change;
		if (angle_wrap < 0)
			angle_wrap += 360;
	}
	return (angle_wrap);
}
