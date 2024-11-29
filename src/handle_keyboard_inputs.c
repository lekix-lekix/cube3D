/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_inputs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:41 by kipouliq          #+#    #+#             */
/*   Updated: 2024/11/29 15:22:18 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_direction_left(t_cub *cub)
{
	if (cub->player.angle == 0)
		cub->player.angle = 360;
	else
		cub->player.angle += 1;
	cub->player.dir = rotate_vector(cub->player.dir, degree_to_rad(1) * -1);
	refresh_raycasting(cub);
	return (0);
}

int	move_direction_right(t_cub *cub)
{
	if (cub->player.angle == 361)
		cub->player.angle = 1;
	else
		cub->player.angle -= 1;
	cub->player.dir = rotate_vector(cub->player.dir, degree_to_rad(1));
	refresh_raycasting(cub);
	return (0);
}

int	strafe(int right, t_cub *cub)
{
	double	next_pos_x;
	double	next_pos_y;
	double	angle;

	if (right == D)
	{
		angle = cub->player.angle - (double)90;
		if (angle < 0)
			angle = fmod(angle, 360);
		next_pos_x = cub->player.pos.x + (cos(degree_to_rad(angle)) * 0.1);
		next_pos_y = cub->player.pos.y - (sin(degree_to_rad(angle)) * 0.1);
	}
	else
	{
		angle = cub->player.angle - (double)90;
		if (angle > 360)
			angle = fmod(angle, 360);
		next_pos_x = cub->player.pos.x - cos(degree_to_rad(angle)) * 0.1;
		next_pos_y = cub->player.pos.y + sin(degree_to_rad(angle)) * 0.1;
	}
	cub->player.pos.x = next_pos_x;
	cub->player.pos.y = next_pos_y;
	refresh_raycasting(cub);
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
	double	modf_var;

	if (fwd)
	{
		next_pos_x = cub->player.pos.x + cos(degree_to_rad(cub->player.angle))
			* 0.2;
		next_pos_y = cub->player.pos.y - sin(degree_to_rad(cub->player.angle))
			* 0.2;
	}
	else
	{
		next_pos_x = cub->player.pos.x - cos(degree_to_rad(cub->player.angle))
			* 0.2;
		next_pos_y = cub->player.pos.y + sin(degree_to_rad(cub->player.angle))
			* 0.2;
	}
	modf(next_pos_y, &modf_var);
	if (cub->map[(int)next_pos_y][(int)cub->player.pos.x] == '1')
	{
		refresh_raycasting(cub);
		return (0);
	}
	cub->player.pos.x = next_pos_x;
	cub->player.pos.y = next_pos_y;
	refresh_raycasting(cub);
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
