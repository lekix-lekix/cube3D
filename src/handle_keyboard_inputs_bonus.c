/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_inputs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:41 by kipouliq          #+#    #+#             */
/*   Updated: 2025/01/16 11:49:33 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_player_movements(t_cub *cub)
{
	if (cub->mov.fwd)
		move_character_in_direction(1, cub);
	if (cub->mov.bwd)
		move_character_in_direction(0, cub);
	if (cub->mov.strafe_r)
		strafe(1, cub);
	if (cub->mov.strafe_l)
		strafe(0, cub);
	if (cub->mov.dir_r)
		move_direction_right(cub);
	if (cub->mov.dir_l)
		move_direction_left(cub);
	refresh_raycasting(cub);
	return (0);
}

void	handle_sky_bool(t_cub *cub)
{
	if (cub->sky_bool)
		cub->sky_bool = false;
	else
		cub->sky_bool = true;
}

int	handle_keypress(int key, t_cub *cub)
{
	if (key == ESCAPE)
		quit_cube(cub);
	if (cub->mov.buffer == 0 || cub->mov.buffer != key)
		cub->mov.buffer = key;
	if (cub->mov.buffer == W)
		cub->mov.fwd = true;
	else if (cub->mov.buffer == S)
		cub->mov.bwd = true;
	else if (cub->mov.buffer == A)
		cub->mov.strafe_l = true;
	else if (cub->mov.buffer == D)
		cub->mov.strafe_r = true;
	else if (cub->mov.buffer == F)
		open_close_door(cub);
	else if (cub->mov.buffer == LEFT)
		cub->mov.dir_l = true;
	else if (cub->mov.buffer == RIGHT)
		cub->mov.dir_r = true;
	else if (cub->mov.buffer == P)
		handle_sky_bool(cub);
	return (0);
}

int	handle_keyrelease(int key, t_cub *cub)
{
	if (key == cub->mov.buffer)
		cub->mov.buffer = 0;
	if (key == W)
		cub->mov.fwd = 0;
	else if (key == S)
		cub->mov.bwd = 0;
	else if (key == A)
		cub->mov.strafe_l = 0;
	else if (key == D)
		cub->mov.strafe_r = 0;
	else if (key == LEFT)
		cub->mov.dir_l = 0;
	else if (key == RIGHT)
		cub->mov.dir_r = 0;
	return (0);
}
