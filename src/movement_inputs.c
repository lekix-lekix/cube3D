/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:44:36 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/02 16:37:07 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_character_left(t_cub *cub)
{
	double	next_pos_x;
	double	modf_var;

	next_pos_x = cub->player.pos.x - 0.1;
	modf(next_pos_x, &modf_var);
	if (cub->map[(int)cub->player.pos.y][(int)next_pos_x] == '1')
		return (0);
	cub->player.pos.x -= 0.1;
	return (0);
}

int	move_character_right(t_cub *cub)
{
	double	next_pos_x;
	double	modf_var;

	next_pos_x = cub->player.pos.x + 0.1;
	modf(next_pos_x, &modf_var);
	if (cub->map[(int)cub->player.pos.y][(int)next_pos_x] == '1')
		return (0);
	cub->player.pos.x += 0.1;
	return (0);
}
