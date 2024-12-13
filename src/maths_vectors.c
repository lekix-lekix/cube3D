/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:32 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/13 15:25:10 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_vector	find_dir(t_cub *cub)
{
	int			x;
	int			y;
	t_vector	vec;

	x = floor(cub->player.pos.x);
	y = floor(cub->player.pos.y);
	vec.x = -1;
	vec.y = -1;
	while (y >= 0)
	{
		if (cub->map[y][x] == '1')
		{
			vec.x = x - cub->player.pos.x;
			vec.y = y - cub->player.pos.y;
			return (vec);
		}
		y--;
	}
	return (vec);
}

t_position	coordinates_to_px(t_cub *cub, double x, double y)
{
	t_position	player_pos;

	player_pos.x = (cub->map_unit * x + 10);
	player_pos.y = (cub->map_unit * y + 10);
	return (player_pos);
}

t_position	get_pos_from_vector(t_position init_pos, t_vector vector)
{
	t_position	new_pos;

	new_pos.x = init_pos.x + vector.x;
	new_pos.y = init_pos.y + vector.y;
	return (new_pos);
}

t_vector	rotate_vector(t_vector vec, double angle)
{
	t_vector	new_vector;
	double		sin_angle;
	double		cos_angle;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	new_vector.x = vec.x * cos_angle - vec.y * sin_angle;
	new_vector.y = vec.x * sin_angle + vec.y * cos_angle;
	return (new_vector);
}

double	degree_to_rad(double degree)
{
	return (degree * PI_RAD);
}
