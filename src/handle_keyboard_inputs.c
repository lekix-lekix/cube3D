/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_inputs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:41 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/11 17:59:41 by kipouliq         ###   ########.fr       */
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

void	check_wall_inc(t_ray *ray, int *x, int *y)
{
	double	modf_var_x;
	double	modf_var_y;
	double	inter_x;
	double	inter_y;

	printf("inter x = %f\n", (*ray).intersection_x);
	inter_x = modf((*ray).intersection_x, &modf_var_x);
	inter_y = modf((*ray).intersection_y, &modf_var_y);
	printf("interx = %f inter y = %f\n", inter_x, inter_y);
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

int	is_oob(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (1);
	if (y >= get_arr_size(map))
		return (1);
	if (x > ft_strlen(map[y]))
		return (1);
	return (0);
}

int	is_player_location(t_player *player, int x, int y)
{
	if ((int)player->pos.x == x && (int)player->pos.y == y)
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
	printf("x_inc = %d y_inc = %d\n", x_inc, y_inc);
	printf("x start = %d y start = %d\n", x, y);
	printf("player pos x = %f y = %f\n", cub->player.pos.x, cub->player.pos.y);
	(void)door;
	while (!is_oob(cub->map, x, y))
	{
		printf("check map x = %d y = %d\n", x, y);
		printf("player pos x = %f y = %f\n", cub->player.pos.x,
			cub->player.pos.y);
		if (cub->map[y][x] == 'O' && !is_player_location(&cub->player, x, y))
		{
			printf("door restored at x %d y %d\n", x, y);
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
	printf("door = %c\n", *door);
	printf("ray.length = %f\n", ray.length);
	if (ray.length < 1 && (*door == 'D'))
	{
		printf("yes door\n");
		*door = 'O';
	}
	else if (ray.length > 0.5 && check_open_door(&ray, cub, &door) == 1)
		*door = 'D';
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
