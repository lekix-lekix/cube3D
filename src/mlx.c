/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/11/12 16:51:03 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	quit_cube(t_cub *cub)
{
	(void)cub;
	printf("quitting\n");
	exit(0);
	return (0);
}

void	find_player_init_pos(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (is_player_direction(cub->map[i][j]))
			{
				cub->player.pos.x = j + 0.5;
				cub->player.pos.y = i + 0.5;
				cub->player.initial_dir = cub->map[i][j];
				return ;
			}
		}
	}
}

void	draw(t_mlx_img *img, t_position pos)
{
	int	i;

	i = 1;
	while (i <= 4)
	{
		img_pix_put(img, pos.x, pos.y - i, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, pos.x - i, pos.y, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, pos.x + i, pos.y, 0xFF0000);
		i++;
	}
}

t_position	coordinates_to_px(double x, double y, int arr_size)
{
	t_position	player_pos;

	(void)arr_size;
	player_pos.x = (ONE_UNIT * x + 10);
	player_pos.y = (ONE_UNIT * y + 10);
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

double	degree_to_rad(int degree)
{
	return (degree * PI_RAD);
}

int	draw_player(t_mlx_img *img, t_cub *cub)
{
	t_position	fov_l;
	t_position	fov_r;
	t_position	dir;
	t_position	px_fov_l;
	t_position	px_fov_r;
	t_position	px_dir;
	t_position	px_player;
	int			arr_size;

	arr_size = get_arr_size(cub->map);
	fov_l = get_pos_from_vector(cub->player.pos, cub->player.fov_l);
	fov_r = get_pos_from_vector(cub->player.pos, cub->player.fov_r);
	dir = get_pos_from_vector(cub->player.pos, cub->player.dir);
	px_fov_l = coordinates_to_px(fov_l.x, fov_l.y, arr_size);
	px_fov_r = coordinates_to_px(fov_r.x, fov_r.y, arr_size);
	px_dir = coordinates_to_px(dir.x, dir.y, arr_size);
	px_player = coordinates_to_px(cub->player.pos.x, cub->player.pos.y,
			arr_size);
	draw(img, coordinates_to_px(cub->player.pos.x, cub->player.pos.y,
			arr_size));
	draw(img, coordinates_to_px(fov_l.x, fov_l.y, arr_size));
	draw(img, coordinates_to_px(fov_r.x, fov_r.y, arr_size));
	draw(img, coordinates_to_px(dir.x, dir.y, arr_size));
	return (0);
}

void	ft_swap(double *a, double *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	draw_ray(t_mlx_img *img, t_position start, t_position end, int arr_size)
{
	start = coordinates_to_px(start.x, start.y, arr_size);
	end = coordinates_to_px(end.x, end.y, arr_size);
	start.x = round(start.x);
	start.y = round(start.y);
	end.x = round(end.x);
	end.y = round(end.y);
	drawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, 0x008000, img);
	return (0);
}

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

int	start_raycasting(t_window_mlx *data, t_cub *cub)
{
	t_mlx_img	*img;

	img = init_img(data);
	if (!img)
		return (error_exit(NULL), -1);
	find_player_init_pos(cub);
	cub->player.dir = find_dir(cub);
	if (cub->player.initial_dir == 'N')
		cub->player.angle = 90;
	else if (cub->player.initial_dir == 'E')
		cub->player.angle = 360;
	else if (cub->player.initial_dir == 'S')
		cub->player.angle = 270;
	else
		cub->player.angle = 180;
	refresh_raycasting(cub);
	mlx_destroy_image(data->mlx_ptr, img->img_ptr);
	return (0);
}

double	find_ray_length(t_cub *cub, double degree_ray_angle)
{
	double	dx;
	double	dy;
	double	dx_sum;
	double	dy_sum;
	int		wall_hit;
	int		x;
	int		y;
	double	ray_length;
	int		last_inc;
	double	modf_var;
	double	modf_real;

	if (degree_ray_angle == 360)
		dy = INFINITY;
	else
		dy = fabs(1 / fabs(sin(degree_to_rad(degree_ray_angle))));
	if (degree_ray_angle == 90)
		dx = INFINITY;
	else
		dx = fabs(1 / fabs(cos(degree_to_rad(degree_ray_angle))));
	x = cub->player.pos.x;
	y = cub->player.pos.y;
	if (modf(cub->player.pos.x, &modf_var))
	{
		if (modf(cub->player.pos.x, &modf_var))
		{
			modf_real = modf(cub->player.pos.x, &modf_var);
			if (degree_ray_angle < 90 || degree_ray_angle > 270)
				dx_sum = fabs((1 - modf_real) * dx);
			else
				dx_sum = fabs(modf_real * dx);
		}
		else
		{
			dx_sum = fabs(dx);
			x -= 1;
		}
	}
	else
		dx_sum = fabs(dx);
	if (modf(cub->player.pos.y, &modf_var))
	{
		if (modf(cub->player.pos.y, &modf_var))
		{
			modf_real = modf(cub->player.pos.y, &modf_var);
			if (degree_ray_angle > 180)
				dy_sum = fabs((1 - modf_real) * dy);
			else
				dy_sum = fabs(modf_real * dy);
		}
		else
			dy_sum = fabs(dy);
	}
	else
		dy_sum = fabs(dy);
	wall_hit = 0;
	last_inc = -1;
	while (!wall_hit && x >= 0 && y >= 0)
	{
		if (cub->map[y][x] == '1')
		{
			if (last_inc == 0)
			{
				ray_length = fabs(dy_sum - dy);
				return (ray_length);
			}
			else
			{
				ray_length = fabs(dx_sum - dx);
				return (ray_length);
			}
			return (ray_length);
		}
		if (dx_sum > dy_sum)
		{
			if (degree_ray_angle > 180 && degree_ray_angle <= 359)
				y++;
			else
				y--;
			dy_sum += dy;
			last_inc = 0;
		}
		else
		{
			if (degree_ray_angle > 90 && degree_ray_angle <= 270)
				x--;
			else
				x++;
			dx_sum += dx;
			last_inc = 1;
		}
	}
	return (-1);
}

t_vector	get_vector_from_length(double ray_length, double degree_angle)
{
	t_vector	ray;

	ray.x = 0;
	ray.y = 0;
	ray.x += ray_length * cos(degree_to_rad(degree_angle));
	ray.y -= ray_length * sin(degree_to_rad(degree_angle));
	// printf("ray x = %f y = %f\n", ray.x, ray.y);
	return (ray);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	draw_vertical_slice(t_mlx_img *img, t_cub *cub, int x, double proj_height,
		int *color_arr, int ray_length)
{
	int	start_y;
	int	end_y;
	int	screen_half;
	int	proj_half;
	int	i;

	screen_half = SCREEN_HEIGHT / 2;
	proj_half = proj_height / 2;
	start_y = screen_half - proj_half;
	end_y = screen_half + proj_half;
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		// printf("x = %d, i = %d\n", x, i);
		while (i < start_y && i < SCREEN_HEIGHT)
		{
			img_pix_put(img, x, i, cub->c_color);
			i++;
		}
		while (i < end_y && i < SCREEN_HEIGHT)
		{
			if (ray_length >= color_arr[0] && ray_length <= color_arr[1])
				img_pix_put(img, x, i, create_trgb(0, 0, 0, 255));
			else if (ray_length >= color_arr[1] && ray_length <= color_arr[2])
				img_pix_put(img, x, i, create_trgb(0, 0, 0, 255 * 0.75));
			else if (ray_length >= color_arr[2] && ray_length <= color_arr[3])
				img_pix_put(img, x, i, create_trgb(0, 0, 0, 255 * 0.50));
			else
				img_pix_put(img, x, i, create_trgb(0, 0, 0, 255 * 0.25));
			i++;
		}
		img_pix_put(img, x, i, cub->f_color);
		i++;
	}
	return (0);
}

int	shoot_rays(t_mlx_img *img, t_cub *cub)
{
	int		color_arr[4];
	int		arr_size;
	double	ray_length;
	int		i;
	double	angle;
	double	ray_inc;
	double	distance_to_proj_plane;
	double	proj_height;
	double	relative_angle;

	i = SCREEN_WIDTH - 1;
	arr_size = get_arr_size(cub->map);
	color_arr[0] = arr_size / 4;
	color_arr[1] = arr_size / 4 * 2;
	color_arr[2] = arr_size / 4 * 3;
	color_arr[3] = arr_size;
	ray_inc = (double)FOV / (double)SCREEN_WIDTH;
	angle = cub->player.angle - (FOV / 2);
	distance_to_proj_plane = (SCREEN_WIDTH / 2) / tan(degree_to_rad(FOV / 2));
	relative_angle = FOV / 2;
	while (i >= 0)
	{
		angle += ray_inc;
		if (angle < 0)
			angle += 360;
		else if (angle > 360)
			angle -= 360;
		ray_length = find_ray_length(cub, angle);
		// printf("ray length = %f\n", ray_length);
		relative_angle -= ray_inc;
		proj_height = distance_to_proj_plane / (ray_length
				* cos(degree_to_rad(relative_angle)));
		draw_vertical_slice(img, cub, i, proj_height, color_arr, ray_length);
		i--;
	}
	return (0);
}

// int	shoot_rays(t_mlx_img *img, t_cub *cub)
// {
// 	int			arr_size;
// 	t_vector	ray;
// 	double		ray_length;
// 	int			i;
// 	int			angle;
// 	double		ray_inc;

// 	arr_size = get_arr_size(cub->map);
// 	i = 0;
// 	// printf("==================\n");
// 	ray_inc = FOV / 60;
// 	// printf("ray inc = %f\n", ray_inc);
// 	angle = cub->player.angle - (FOV / 2);
// 	printf("player pos x = %f y = %f\n", cub->player.pos.x, cub->player.pos.y);
// 	while (i < 60)
// 	{
// 		angle += ray_inc;
// 		if (angle < 0)
// 			angle += 360;
// 		else if (angle > 360)
// 			angle -= 360;
// 		// printf("angle = %d\n", angle);
// 		ray_length = find_ray_length(cub, angle);
// 		printf("ray lenght = %f\n", ray_length);
// 		ray = get_vector_from_length(ray_length, angle);
// 		draw_ray(img, cub->player.pos, get_pos_from_vector(cub->player.pos,
// 				ray), arr_size);
// 		i++;
// 	}
// 	return (0);
// }

int	refresh_raycasting(t_cub *cub)
{
	t_mlx_img	*img;
	int			arr_size;

	arr_size = get_arr_size(cub->map);
	img = init_img(&cub->mlx_data);
	if (!img)
		return (error_exit(NULL), -1);
	// printf("player pos = x %f y %f\n", cub->player.pos.x, cub->player.pos.y);
	// draw_map(img, cub->map);
	shoot_rays(img, cub);
	mlx_put_image_to_window(cub->mlx_data.mlx_ptr, cub->mlx_data.win_ptr,
		img->img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx_data.mlx_ptr, img->img_ptr);
	return (0);
}

int	start_mlx(int height, int width, t_cub *cub)
{
	cub->mlx_data.mlx_ptr = mlx_init();
	cub->mlx_data.width = width;
	cub->mlx_data.height = height;
	if (!cub->mlx_data.mlx_ptr)
		return (-1);
	cub->mlx_data.win_ptr = mlx_new_window(cub->mlx_data.mlx_ptr, width, height,
			"cub3D");
	if (!cub->mlx_data.win_ptr)
		return (-1);
	start_raycasting(&cub->mlx_data, cub);
	// mlx_key_hook(cub->mlx_data.win_ptr, handle_keyboard_inputs, cub);
	mlx_hook(cub->mlx_data.win_ptr, 2, (1L << 0), handle_keyboard_inputs, cub);
	mlx_loop(cub->mlx_data.mlx_ptr);
	return (0);
}
