/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:44:36 by kipouliq          #+#    #+#             */
/*   Updated: 2024/11/08 15:17:48 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_character_up(t_cub *cub)
{
	double	next_pos_y;
	double	modf_var;

	next_pos_y = cub->player.pos.y - 0.1;
	modf(next_pos_y, &modf_var);
	if (cub->map[(int)next_pos_y][(int)cub->player.pos.x] == '1')
	{
		refresh_raycasting(cub);
		return (0);
	}
	cub->player.pos.y -= 0.1;
	refresh_raycasting(cub);
	return (0);
}

int	move_character_down(t_cub *cub)
{
	double	next_pos_y;
	double	modf_var;

	next_pos_y = cub->player.pos.y + 0.1;
	modf(next_pos_y, &modf_var);
	if (cub->map[(int)next_pos_y][(int)cub->player.pos.x] == '1')
	{
		refresh_raycasting(cub);
		return (0);
	}
	cub->player.pos.y += 0.1;
	refresh_raycasting(cub);
	return (0);
}

int	move_character_left(t_cub *cub)
{
	double	next_pos_x;
	double	modf_var;

	next_pos_x = cub->player.pos.x - 0.1;
	modf(next_pos_x, &modf_var);
	if (cub->map[(int)cub->player.pos.y][(int)next_pos_x] == '1')
	{
		refresh_raycasting(cub);
		return (0);
	}
    cub->player.pos.x -= 0.1;
	refresh_raycasting(cub);
	return (0);
}

int	move_character_right(t_cub *cub)
{
	double	next_pos_x;
	double	modf_var;

	next_pos_x = cub->player.pos.x + 0.1;
	modf(next_pos_x, &modf_var);
	if (cub->map[(int)cub->player.pos.y][(int)next_pos_x] == '1')
	{
		refresh_raycasting(cub);
		return (0);
	}
    cub->player.pos.x += 0.1;
	refresh_raycasting(cub);
	return (0);
}
