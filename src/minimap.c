/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:49:33 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/25 11:36:36 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	draw_x_line(t_mlx_img *img, int x_pos, int y_pos, int color)
{
	int	x_max;

	x_max = x_pos + ONE_UNIT;
	while (x_pos < x_max)
	{
		img_pix_put(img, x_pos, y_pos, color);
		x_pos++;
	}
	return (0);
}

int fill_x_line(t_mlx_img *img, int x_pos, int y_pos, int color)
{
    int x_max;

    x_max = x_pos + ONE_UNIT;
    while (++x_pos < x_max)
        img_pix_put(img, x_pos, y_pos, color);
    return (0);
}

int	draw_y_line(t_mlx_img *img, int x_pos, int y_pos_init, char terrain)
{
	int	y_pos;
	int	y_max;

    (void) terrain;     
	y_pos = y_pos_init;
	y_max = y_pos + ONE_UNIT;
	while (y_pos < y_max)
	{
		img_pix_put(img, x_pos, y_pos, 0x808080);
        if (terrain == '1')
            draw_x_line(img, x_pos + 1, y_pos, 0xFFFFFF);
		y_pos += 1;
	}
	return (0);
}

int	draw_map(t_mlx_img *img, char **map)
{
	int	i;
	int	j;
	int	px_x_pos;
	int	px_y_pos;

	i = -1;
	px_y_pos = 10;
	while (map[++i])
	{
		j = -1;
		px_x_pos = 10;
		while (map[i][++j])
		{
			if (!ft_is_space(map[i][j]))
			{
				draw_y_line(img, px_x_pos, px_y_pos, map[i][j]);
				draw_x_line(img, px_x_pos, px_y_pos, 0x808080);
                px_x_pos += ONE_UNIT;
			}
		}
		draw_y_line(img, px_x_pos, px_y_pos, map[i][j]);
		px_y_pos += ONE_UNIT;
	}
	i = 0;
	px_x_pos = 10;
	while (i < (int)ft_strlen(map[get_arr_size(map) - 1]))
    {
		draw_x_line(img, px_x_pos, px_y_pos, 0x808080);
        px_x_pos += ONE_UNIT;
        i++;
    }
	return (0);
}
