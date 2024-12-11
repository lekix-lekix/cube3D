/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:55:23 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/11 18:21:07 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_vector	get_wall_side_collision(t_ray *collision_ray)
{
	double		modf_var_x;
	double		modf_var_y;
	t_vector	wall;

	collision_ray->intersection_x = modf(collision_ray->intersection_x,
			&modf_var_x);
	if (!collision_ray->intersection_x)
	{
		collision_ray->intersection_x = modf(collision_ray->intersection_y,
				&modf_var_y);
		wall.y = 0;
		if (collision_ray->angle >= 90 && collision_ray->angle <= 270)
			wall.x = -1;
		else
			wall.x = 1;
	}
	else
	{
		wall.x = 0;
		if (collision_ray->angle >= 180 && collision_ray->angle <= 360)
			wall.y = -1;
		else
			wall.y = 1;
	}
	return (wall);
}

t_vector	calc_updated_player_vec(t_vector player_vec, t_vector wall_vec)
{
	t_vector	updated_player_vec;
	t_vector	norm_vec;
	double		dot_product;

	dot_product = (player_vec.x * wall_vec.x) + (player_vec.y * wall_vec.y);
	norm_vec.x = wall_vec.x * dot_product;
	norm_vec.y = wall_vec.y * dot_product;
	updated_player_vec.x = (player_vec.x - norm_vec.x) * 0.2;
	updated_player_vec.y = (player_vec.y - norm_vec.y) * 0.2;
	return (updated_player_vec);
}

t_position	find_collision_player_pos(t_ray *next_pos_ray, t_cub *cub)
{
	t_vector	ray_vec;
	t_vector	wall_vec;
	t_vector	new_player_vec;
	t_position	new_player_pos;

	ray_vec = get_vector_from_length(next_pos_ray->length, next_pos_ray->angle);
	wall_vec = get_wall_side_collision(next_pos_ray);
	new_player_vec = calc_updated_player_vec(ray_vec, wall_vec);
	new_player_pos = get_pos_from_vector(cub->player.pos, new_player_vec);
	return (new_player_pos);
}

int	check_wall_collision(t_cub *cub, char dir)
{
	t_ray	next_pos_ray;

	if (dir == 'W')
		next_pos_ray.angle = cub->player.angle;
	else if (dir == 'S')
		next_pos_ray.angle = wrap_angle_360(cub->player.angle, 180, false);
	else if (dir == 'A')
		next_pos_ray.angle = wrap_angle_360(cub->player.angle, 90, true);
	else
		next_pos_ray.angle = wrap_angle_360(cub->player.angle, 90, false);
	next_pos_ray.length = find_ray_length(cub, &next_pos_ray);
	if (((dir == 'A' || dir == 'D') && next_pos_ray.length < 0.1)
		|| ((dir == 'W' || dir == 'S') && next_pos_ray.length < 0.4))
	{
		cub->player.pos = find_collision_player_pos(&next_pos_ray, cub);
		return (1);
	}
	return (0);
}
