/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:38:37 by lekix             #+#    #+#             */
/*   Updated: 2024/12/03 16:11:08 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))
#define SGN(_x) ((_x) < 0 ? -1 : ((_x) > 0 ? 1 : 0))

void	drawLine(int x0, int y0, int x1, int y1, int c, t_mlx_img *img)
{
	// printf("x0 = %d y0 = %d x1 = %d y1 = %d\n", x0, y0, x1, y1);
	if (x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0 )
		return ;
	int dx = x1 - x0;
	int dy = y1 - y0;
	int incX = SGN(dx);
	int incY = SGN(dy);
	dx = ABS(dx);
	dy = ABS(dy);

	if (dy == 0)
	{
		// horizontal line
		for (int x = x0; x != x1 + incX; x += incX)
			img_pix_put(img, x, y0, c);
	}
	else if (dx == 0)
	{
		// vertical line
		for (int y = y0; y != y1 + incY; y += incY)
			img_pix_put(img, x0, y, c);
	}
	else if (dx >= dy)
	{
		// more horizontal than vertical
		int slope = 2 * dy;
		int error = -dx;
		int errorInc = -2 * dx;
		int y = y0;

		for (int x = x0; x != x1 + incX; x += incX)
		{
			img_pix_put(img, x, y, c);
			error += slope;

			if (error >= 0)
			{
				y += incY;
				error += errorInc;
			}
		}
	}
	else
	{
		// more vertical than horizontal
		int slope = 2 * dx;
		int error = -dy;
		int errorInc = -2 * dy;
		int x = x0;

		for (int y = y0; y != y1 + incY; y += incY)
		{
			img_pix_put(img, x, y, c);
			error += slope;

			if (error >= 0)
			{
				x += incX;
				error += errorInc;
			}
		}
	}
}