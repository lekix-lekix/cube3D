/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_inputs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:41 by kipouliq          #+#    #+#             */
/*   Updated: 2024/11/04 16:28:53 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_direction_left(t_cub *cub)
{
	if (cub->player.angle == 0)
		cub->player.angle = 360;
	else
		cub->player.angle -= 1;
	cub->player.dir = rotate_vector(cub->player.dir, degree_to_rad(1) * -1);
	refresh_raycasting(cub);
	return (0);
}

int	move_direction_right(t_cub *cub)
{
	if (cub->player.angle == 359)
		cub->player.angle = 1;
	else
		cub->player.angle += 1;
	cub->player.dir = rotate_vector(cub->player.dir, degree_to_rad(1));
	refresh_raycasting(cub);
	return (0);
}

int	move_direction(int key, t_cub *cub)
{
	if (key == LEFT)
		return (move_direction_left(cub));
	else if (key == RIGHT)
		return (move_direction_right(cub));
	return (0);
}

int	move_character(int key, t_cub *cub)
{
	if (key == W)
		return (move_character_up(cub));
	else if (key == S)
		return (move_character_down(cub));
	else if (key == A)
		return (move_character_left(cub));
	else if (key == D)
		return (move_character_right(cub));
	return (0);
}

int	handle_keyboard_inputs(int key, t_cub *cub)
{
	if (key == LEFT || key == RIGHT)
		return (move_direction(key, cub));
	else if (key == W || key == A || key == S || key == D)
		return (move_character(key, cub));
	else if (key == ESCAPE)
		return (quit_cube(cub));
	return (0);
}
