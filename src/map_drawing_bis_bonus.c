/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:44:26 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/13 15:25:31 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw(t_mlx_img *img, t_position pos)
{
	int	i;

	i = 1;
	while (i <= 4)
	{
		img_pix_put(img, pos.x, pos.y - i, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, pos.x - i, pos.y, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, pos.x + i, pos.y, 0xFF0000);
		i++;
	}
}

int	draw_player(t_mlx_img *img, t_cub *cub)
{
	t_position	fov_l;
	t_position	fov_r;
	t_position	dir;
	int			arr_size;

	arr_size = get_arr_size(cub->map);
	fov_l = get_pos_from_vector(cub->player.pos, cub->player.fov_l);
	fov_r = get_pos_from_vector(cub->player.pos, cub->player.fov_r);
	dir = get_pos_from_vector(cub->player.pos, cub->player.dir);
	draw(img, coordinates_to_px(cub, cub->player.pos.x, cub->player.pos.y));
	draw(img, coordinates_to_px(cub, fov_l.x, fov_l.y));
	draw(img, coordinates_to_px(cub, fov_r.x, fov_r.y));
	draw(img, coordinates_to_px(cub, dir.x, dir.y));
	return (0);
}

int	draw_ray(t_cub *cub, t_mlx_img *img, t_position start, t_position end)
{
	int	arr_size;

	arr_size = size_tab(cub->map);
	start = coordinates_to_px(cub, start.x, start.y);
	end = coordinates_to_px(cub, end.x, end.y);
	start.x = round(start.x);
	start.y = round(start.y);
	end.x = round(end.x);
	end.y = round(end.y);
	draw_line(start, end, create_trgb(0, 0, 255, 0), img);
	return (0);
}

int	draw_map_rays(t_mlx_img *img, t_cub *cub, t_vector *map_rays)
{
	int	i;
	int	arr_size;

	i = SCREEN_WIDTH;
	arr_size = get_arr_size(cub->map);
	while (i >= 0)
	{
		draw_ray(cub, img, cub->player.pos, get_pos_from_vector(cub->player.pos,
				map_rays[i]));
		i--;
	}
	return (0);
}
