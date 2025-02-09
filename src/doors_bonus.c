/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:00:25 by kipouliq          #+#    #+#             */
/*   Updated: 2025/02/09 19:39:10 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_wall_inc(t_ray *ray, int *x, int *y)
{
	double	modf_var_x;
	double	inter_x;

	inter_x = modf((*ray).intersection_x, &modf_var_x);
	if (!inter_x)
	{
		*y = 0;
		if ((*ray).angle >= 90 && (*ray).angle <= 270)
			*x = 1;
		else
			*x = -1;
	}
	else
	{
		*x = 0;
		if ((*ray).angle >= 180 && (*ray).angle <= 360)
			*y = -1;
		else
			*y = 1;
	}
}

int	is_player_location(t_player *player, int x, int y)
{
	if ((int)player->pos.x == x && (int)player->pos.y == y)
		return (1);
	return (0);
}

int	is_oob(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (1);
	if (y >= get_arr_size(map))
		return (1);
	if (x > (int)ft_strlen(map[y]))
		return (1);
	return (0);
}

int	check_open_door(t_ray *ray, t_cub *cub, char **door)
{
	int	x;
	int	y;
	int	x_inc;
	int	y_inc;

	check_wall_inc(ray, &x_inc, &y_inc);
	x = ray->intersection_x;
	y = ray->intersection_y;
	while (!is_oob(cub->map, x, y))
	{
		if (cub->map[y][x] == 'O' && !is_player_location(&cub->player, x, y))
		{
			*door = &cub->map[y][x];
			return (1);
		}
		x += x_inc;
		y += y_inc;
	}
	return (-1);
}

int	open_close_door(t_cub *cub)
{
	t_ray	ray;
	char	*door;

	ray.angle = cub->player.angle;
	ray.length = find_ray_length(cub, &ray);
	door = &cub->map[(int)ray.intersection_y][(int)ray.intersection_x];
	if (ray.length < 1 && (*door == 'D'))
		*door = 'O';
	else if (ray.length > 0.5 && check_open_door(&ray, cub, &door) == 1)
		*door = 'D';
	return (0);
}
