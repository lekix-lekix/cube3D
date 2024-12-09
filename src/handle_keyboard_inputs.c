/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_inputs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:41 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/09 18:41:51 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	wrap_angle_360(double angle, double change, bool add)
{
	double	angle_wrap;

	if (add)
	{
		angle_wrap = angle + change;
		if (angle_wrap > 360)
			angle_wrap = fmod(angle_wrap, 360);
	}
	else
	{
		angle_wrap = angle - change;
		if (angle_wrap < 0)
			angle_wrap += 360;
	}
	return (angle_wrap);
}

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

t_vector	get_wall_side_collision(t_ray *collision_ray)
{
	double		modf_var_x;
	double		modf_var_y;
	t_vector	wall;

	collision_ray->intersection_x = modf(collision_ray->intersection_x,
			&modf_var_x);
	if (!collision_ray->intersection_x)
	{
		collision_ray->intersection_x = modf(collision_ray->intersection_y,
				&modf_var_y);
		wall.y = 0;
		if (collision_ray->angle >= 90 && collision_ray->angle <= 270)
			wall.x = -1;
		else
			wall.x = 1;
	}
	else
	{
		wall.x = 0;
		if (collision_ray->angle >= 180 && collision_ray->angle <= 360)
			wall.y = -1;
		else
			wall.y = 1;
	}
	return (wall);
}

t_vector	calc_updated_player_vec(t_vector player_vec, t_vector wall_vec)
{
	t_vector	updated_player_vec;
	t_vector	norm_vec;
	double		dot_product;

	dot_product = (player_vec.x * wall_vec.x) + (player_vec.y * wall_vec.y);
	norm_vec.x = wall_vec.x * dot_product;
	norm_vec.y = wall_vec.y * dot_product;
	updated_player_vec.x = (player_vec.x - norm_vec.x) * 0.2;
	updated_player_vec.y = (player_vec.y - norm_vec.y) * 0.2;
	return (updated_player_vec);
}

t_position	find_collision_player_pos(t_ray *next_pos_ray, t_cub *cub)
{
	t_vector	ray_vec;
	t_vector	wall_vec;
	t_vector	new_player_vec;
	t_position	new_player_pos;

	ray_vec = get_vector_from_length(next_pos_ray->length, next_pos_ray->angle);
	wall_vec = get_wall_side_collision(next_pos_ray);
	new_player_vec = calc_updated_player_vec(ray_vec, wall_vec);
	new_player_pos = get_pos_from_vector(cub->player.pos, new_player_vec);
	return (new_player_pos);
}

int	check_wall_collision(t_cub *cub, char dir)
{
	t_ray	next_pos_ray;

	if (dir == 'W')
		next_pos_ray.angle = cub->player.angle;
	else if (dir == 'S')
		next_pos_ray.angle = wrap_angle_360(cub->player.angle, 180, false);
	else if (dir == 'A')
		next_pos_ray.angle = wrap_angle_360(cub->player.angle, 90, true);
	else
		next_pos_ray.angle = wrap_angle_360(cub->player.angle, 90, false);
	next_pos_ray.length = find_ray_length(cub, &next_pos_ray);
	if (((dir == 'A' || dir == 'D') && next_pos_ray.length < 0.1)
		|| ((dir == 'W' || dir == 'S') && next_pos_ray.length < 0.4))
	{
		cub->player.pos = find_collision_player_pos(&next_pos_ray, cub);
		return (1);
	}
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
	(void)door;
	while ((x != cub->player.pos.x && y != cub->player.pos.y)
		|| !is_oob(cub->map, x, y))
	{
		printf("check map x = %d y = %d\n", x, y);
		if (cub->map[y][x] == 'O' && (int)cub->player.pos.x != x
			&& (int)cub->player.pos.y != y)
		{
			printf("player pos x = %f y = %f\n", cub->player.pos.x,
				cub->player.pos.y);
			printf("door restored\n");
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
	if (ray.length < 1 && (*door == 'D'))
	{
		printf("yes door\n");
		*door = 'O';
	}
	else if (check_open_door(&ray, cub, &door) == 1)
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
