/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:44:36 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/12 14:05:43 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_direction_left(t_cub *cub)
{
	cub->player.angle = wrap_angle_360(cub->player.angle, 0.8, true);
	cub->player.dir = rotate_vector(cub->player.dir, degree_to_rad(0.8) * -1);
	return (0);
}

int	move_direction_right(t_cub *cub)
{
	cub->player.angle = wrap_angle_360(cub->player.angle, 0.8, false);
	cub->player.dir = rotate_vector(cub->player.dir, degree_to_rad(0.8));
	return (0);
}

int	strafe(int right, t_cub *cub)
{
	double	next_pos_x;
	double	next_pos_y;
	double	angle;

	angle = wrap_angle_360(cub->player.angle, 90, false);
	if (right)
	{
		next_pos_x = cub->player.pos.x + (cos(degree_to_rad(angle)) * 0.03);
		next_pos_y = cub->player.pos.y - (sin(degree_to_rad(angle)) * 0.03);
		if (check_wall_collision(cub, 'D'))
			return (1);
	}
	else
	{
		next_pos_x = cub->player.pos.x - (cos(degree_to_rad(angle)) * 0.03);
		next_pos_y = cub->player.pos.y + (sin(degree_to_rad(angle)) * 0.03);
		if (check_wall_collision(cub, 'A'))
			return (1);
	}
	cub->player.pos.x = next_pos_x;
	cub->player.pos.y = next_pos_y;
	return (0);
}

int	move_character_in_direction(int fwd, t_cub *cub)
{
	double	next_pos_y;
	double	next_pos_x;

	if (fwd)
	{
		next_pos_x = cub->player.pos.x + cos(degree_to_rad(cub->player.angle))
			* 0.05;
		next_pos_y = cub->player.pos.y - sin(degree_to_rad(cub->player.angle))
			* 0.05;
		if (check_wall_collision(cub, 'W'))
			return (1);
	}
	else
	{
		next_pos_x = cub->player.pos.x - cos(degree_to_rad(cub->player.angle))
			* 0.05;
		next_pos_y = cub->player.pos.y + sin(degree_to_rad(cub->player.angle))
			* 0.05;
		if (check_wall_collision(cub, 'S'))
			return (1);
	}
	cub->player.pos.x = next_pos_x;
	cub->player.pos.y = next_pos_y;
	return (0);
}
