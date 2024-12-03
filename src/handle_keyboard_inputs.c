/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_inputs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:41 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/03 17:59:49 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_direction_left(t_cub *cub)
{
	if (cub->player.angle == 0)
		cub->player.angle = 360;
	else
		cub->player.angle += 0.8;
	cub->player.dir = rotate_vector(cub->player.dir, degree_to_rad(1) * -1);
	return (0);
}

int	move_direction_right(t_cub *cub)
{
	if (cub->player.angle == 361)
		cub->player.angle = 1;
	else
		cub->player.angle -= 0.8;
	cub->player.dir = rotate_vector(cub->player.dir, degree_to_rad(1));
	return (0);
}

int	check_wall_collision(t_cub *cub)
{
	t_ray	next_pos_ray;

	next_pos_ray.angle = cub->player.angle;
	next_pos_ray.length = find_ray_length(cub, &next_pos_ray);
    if (next_pos_ray.length < 0.5)
	printf("next pos ray = %f\n", next_pos_ray.length);
	return (0);
}

int	strafe(int right, t_cub *cub)
{
	double	next_pos_x;
	double	next_pos_y;
	double	angle;

	if (right)
	{
		angle = cub->player.angle - (double)90;
		if (angle < 0)
			angle = fmod(angle, 360);
		next_pos_x = cub->player.pos.x + (cos(degree_to_rad(angle)) * 0.05);
		next_pos_y = cub->player.pos.y - (sin(degree_to_rad(angle)) * 0.05);
	}
	else
	{
		angle = cub->player.angle - (double)90;
		if (angle > 360)
			angle = fmod(angle, 360);
		next_pos_x = cub->player.pos.x - (cos(degree_to_rad(angle)) * 0.05);
		next_pos_y = cub->player.pos.y + (sin(degree_to_rad(angle)) * 0.05);
	}
	if (check_wall_collision(cub))
	{
		cub->player.pos.y = next_pos_y;
		return (-1);
	}
	cub->player.pos.x = next_pos_x;
	cub->player.pos.y = next_pos_y;
	return (0);
}

int	change_direction(int key, t_cub *cub)
{
	if (key == LEFT)
		return (move_direction_left(cub));
	else if (key == RIGHT)
		return (move_direction_right(cub));
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
	}
	else
	{
		next_pos_x = cub->player.pos.x - cos(degree_to_rad(cub->player.angle))
			* 0.05;
		next_pos_y = cub->player.pos.y + sin(degree_to_rad(cub->player.angle))
			* 0.05;
	}
	if (check_wall_collision(cub))
		return (-1);
	cub->player.pos.x = next_pos_x;
	cub->player.pos.y = next_pos_y;
	return (0);
}

int	handle_keyboard_inputs(int key, t_cub *cub)
{
	if (key == LEFT || key == RIGHT)
		return (change_direction(key, cub));
	else if (key == W || key == S)
		return (move_character_in_direction(key, cub));
	else if (key == A || key == D)
		return (strafe(key, cub));
	else if (key == ESCAPE)
		return (quit_cube(cub));
	return (0);
}
