/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:38:37 by lekix             #+#    #+#             */
/*   Updated: 2024/12/12 15:30:32 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	define_inc(int x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	return (0);
}

int	draw_line_straight(t_position *start, t_position *end, int color,
		t_mlx_img *img)
{
	int	inc;
	int	x;

	if (end->y - start->y == 0)
	{
		x = start->x;
		inc = define_inc(end->x - start->x);
		while (x != end->x + inc)
		{
			img_pix_put(img, x, start->y, color);
			x += inc;
		}
	}
	else if (end->x - start->x == 0)
	{
		x = start->y;
		inc = define_inc(end->y - start->y);
		while (x != end->y)
		{
			img_pix_put(img, start->x, x, color);
			x += inc;
		}
	}
	return (0);
}

int	draw_slope_horizontal(t_position *start, t_position *end, int color,
		t_mlx_img *img)
{
	int	error;
	int	error_inc;
	int	x;
	int	y;

	error = fabs(end->x - start->x) * -1;
	error_inc = -2 * fabs(end->x - start->x);
	x = start->x;
	y = start->y;
	while (x != end->x + define_inc(end->x - start->x))
	{
		img_pix_put(img, x, y, color);
		error += 2 * fabs(end->y - start->y);
		if (error >= 0)
		{
			y += define_inc(end->y - start->y);
			error += error_inc;
		}
		x += define_inc(end->x - start->x);
	}
	return (0);
}

int	draw_slope_vertical(t_position *start, t_position *end, int color,
		t_mlx_img *img)
{
	int	error;
	int	error_inc;
	int	x;
	int	y;

	error = fabs(end->y - start->y) * -1;
	error_inc = -2 * fabs(end->y - start->y);
	x = start->x;
	y = start->y;
	while (y != end->y + define_inc(end->y - start->y))
	{
		img_pix_put(img, x, y, color);
		error += 2 * fabs(end->x - start->x);
		if (error >= 0)
		{
			x += define_inc(end->x - start->x);
			error += error_inc;
		}
		y += define_inc(end->y - start->y);
	}
	return (0);
}

int	draw_line(t_position start, t_position end, int color, t_mlx_img *img)
{
	int	dx;
	int	dy;
	int	inc_x;
	int	inc_y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	inc_x = define_inc(dx);
	inc_y = define_inc(dy);
	dx = abs(dx);
	dy = abs(dy);
	if (start.x < 0 || start.y < 0 || end.x < 0 || end.y < 0)
		return (0);
	if (end.x - start.x == 0 || end.y - start.y == 0)
		return (draw_line_straight(&start, &end, color, img));
	else if (fabs(end.x - start.x) >= fabs(end.y - start.y))
		return (draw_slope_horizontal(&start, &end, color, img));
	else
		return (draw_slope_vertical(&start, &end, color, img));
	return (0);
}
