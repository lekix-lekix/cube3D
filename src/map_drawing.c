/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:49:33 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/13 15:15:06 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	draw_x_line(t_mlx_img *img, int x_pos, int y_pos, int color, int unit)
{
	int	x_max;

	x_max = x_pos + unit;
	while (x_pos < x_max)
	{
		img_pix_put(img, x_pos, y_pos, color);
		x_pos++;
	}
	return (0);
}

int	fill_x_line(t_mlx_img *img, int x_pos, int y_pos, int color, int unit)
{
	int	x_max;

	x_max = x_pos + unit;
	while (++x_pos < x_max)
		img_pix_put(img, x_pos, y_pos, color);
	return (0);
}

int	draw_y_line(t_mlx_img *img, int x_pos, int y_pos_init, char terrain, int unit)
{
	int	y_pos;
	int	y_max;

	y_pos = y_pos_init;
	y_max = y_pos + unit;
	while (y_pos < y_max)
	{
		img_pix_put(img, x_pos, y_pos, 0x808080);
		if (terrain == '1')
			draw_x_line(img, x_pos + 1, y_pos, 0xFFFFFF, unit);
		y_pos += 1;
	}
	return (0);
}

void	draw_last_line(t_mlx_img *img, char **map, int px_y_pos, int unit)
{
	int	i;
	int	px_x_pos;

	i = 0;
	px_x_pos = 10;
	while (i < (int)ft_strlen(map[get_arr_size(map) - 1]))
	{
		draw_x_line(img, px_x_pos, px_y_pos, 0x808080, unit);
		px_x_pos += unit;
		i++;
	}
}

int	draw_map(t_mlx_img *img, t_cub *cub)
{
	int	i;
	int	j;
	int	px_x_pos;
	int	px_y_pos;
    int unit;
    
    unit = cub->map_unit;
	i = -1;
	px_y_pos = 10;
	while (cub->map[++i])
	{
		j = -1;
		px_x_pos = 10;
		while (cub->map[i][++j])
		{
			if (!ft_is_space(cub->map[i][j]))
			{
				draw_y_line(img, px_x_pos, px_y_pos, cub->map[i][j], unit);
				draw_x_line(img, px_x_pos, px_y_pos, 0x808080, unit);
				px_x_pos += unit;
			}
		}
		draw_y_line(img, px_x_pos, px_y_pos, cub->map[i][j], unit);
		px_y_pos += unit;
	}
	draw_last_line(img, cub->map, px_y_pos, unit);
	return (0);
}
