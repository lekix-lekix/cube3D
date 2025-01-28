/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:32:51 by kipouliq          #+#    #+#             */
/*   Updated: 2025/01/28 16:14:30 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_ray	init_ray(double player_angle)
{
	t_ray	ray;

	ray.angle_inc = (double)FOV / (double)SCREEN_WIDTH;
	ray.angle = player_angle - (double)(FOV / 2);
	ray.distance_to_proj_plane = (SCREEN_WIDTH / 5) / tan(degree_to_rad(FOV
				/ 2));
	ray.relative_angle = (double)FOV / (double)2;
	return (ray);
}

int	shoot_rays(t_mlx_img *img, t_cub *cub, t_vector *map_rays)
{
	t_ray	ray;
	int		i;

	i = SCREEN_WIDTH;
	ray = init_ray(cub->player.angle);
	while (i >= 0)
	{
		ray.angle += ray.angle_inc;
		if (ray.angle < 0)
			ray.angle += (double)360;
		else if (ray.angle > 360)
			ray.angle -= (double)360;
		ray.length = find_ray_length(cub, &ray);
		ray.relative_angle -= ray.angle_inc;
		ray.proj_height = ray.distance_to_proj_plane / (ray.length
				* cos(degree_to_rad(ray.relative_angle)));
		map_rays[i] = get_vector_from_length(ray.length, ray.angle);
		draw_vertical_slice(img, cub, i, &ray);
		i--;
	}
	return (0);
}

double	wall_hit(t_ray *ray, t_position player_pos, t_dda_vars vars,
		int last_inc)
{
	if (last_inc == 0)
	{
		(*ray).intersection_x = player_pos.x + cos(degree_to_rad((*ray).angle))
			* (vars.dy_sum - vars.dy);
		(*ray).intersection_y = vars.y;
		return (fabs(vars.dy_sum - vars.dy));
	}
	else
	{
		(*ray).intersection_x = vars.x;
		(*ray).intersection_y = player_pos.y - (sin(degree_to_rad((*ray).angle))
				* (vars.dx_sum - vars.dx));
		return (fabs(vars.dx_sum - vars.dx));
	}
}

int	refresh_raycasting(t_cub *cub)
{
	t_mlx_img	*img;
	t_vector	*map_rays;

	img = init_img(&cub->mlx_data, cub);
	if (!img)
		return (error_exit(MEM_ERROR, cub), -1);
	map_rays = malloc(sizeof(t_vector) * (SCREEN_WIDTH + 1));
	if (!map_rays)
		return (mlx_destroy_image(cub->mlx_data.mlx_ptr, img->img_ptr),
			free(img), error_exit(MEM_ERROR, cub), -1);
	shoot_rays(img, cub, map_rays);
	draw_map(img, cub);
	draw_map_rays(img, cub, map_rays);
	mlx_put_image_to_window(cub->mlx_data.mlx_ptr, cub->mlx_data.win_ptr,
		img->img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx_data.mlx_ptr, img->img_ptr);
	free(map_rays);
	free(img);
	return (0);
}

int	start_raycasting(t_cub *cub)
{
	find_player_init_pos(cub);
	cub->player.dir = find_dir(cub);
	if (cub->player.initial_dir == 'N')
		cub->player.angle = 90;
	else if (cub->player.initial_dir == 'E')
		cub->player.angle = 360;
	else if (cub->player.initial_dir == 'S')
		cub->player.angle = 270;
	else
		cub->player.angle = 180;
	refresh_raycasting(cub);
	return (0);
}
