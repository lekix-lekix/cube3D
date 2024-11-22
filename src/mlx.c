/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/11/22 18:19:18 by kipouliq         ###   ########.fr       */
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

double	degree_to_rad(double degree)
{
	return (degree * PI_RAD);
}

int	draw_player(t_mlx_img *img, t_cub *cub)
{
	t_position	fov_l;
	t_position	fov_r;
	t_position	dir;
	int			arr_size;

	// t_position	px_fov_l;
	// t_position	px_fov_r;
	// t_position	px_dir;
	// t_position	px_player;
	arr_size = get_arr_size(cub->map);
	fov_l = get_pos_from_vector(cub->player.pos, cub->player.fov_l);
	fov_r = get_pos_from_vector(cub->player.pos, cub->player.fov_r);
	dir = get_pos_from_vector(cub->player.pos, cub->player.dir);
	// px_fov_l = coordinates_to_px(fov_l.x, fov_l.y, arr_size);
	// px_fov_r = coordinates_to_px(fov_r.x, fov_r.y, arr_size);
	// px_dir = coordinates_to_px(dir.x, dir.y, arr_size);
	// px_player = coordinates_to_px(cub->player.pos.x, cub->player.pos.y,
	// arr_size);
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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	draw_ray(t_mlx_img *img, t_position start, t_position end, int arr_size)
{
	start = coordinates_to_px(start.x, start.y, arr_size);
	end = coordinates_to_px(end.x, end.y, arr_size);
	start.x = round(start.x);
	start.y = round(start.y);
	end.x = round(end.x);
	end.y = round(end.y);
	drawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, create_trgb(0,
			0, 255, 0), img);
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

double	find_ray_length(t_cub *cub, double degree_ray_angle,
		double *intersection_x, double *intersection_y)
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
				*intersection_x = cub->player.pos.x
					+ cos(degree_to_rad(degree_ray_angle)) * (dy_sum - dy);
				*intersection_y = y;
				// printf("wall hit dy intersection x = %f y = %f\n",
				// *intersection_x, *intersection_y);
				// printf("mod x = %f\n", fmod(*intersection_x, 1.0));
				return (ray_length);
			}
			else
			{
				ray_length = fabs(dx_sum - dx);
				*intersection_x = x;
				*intersection_y = cub->player.pos.y
					- (sin(degree_to_rad(degree_ray_angle)) * (dx_sum - dx));
				// printf("wall hit dx intersection x = %f y = %f\n",
				// *intersection_x, *intersection_y);
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
	// printf("degree angle = %f\n", degree_angle);
	ray.x += ray_length * cos(degree_to_rad(degree_angle));
	ray.y -= ray_length * sin(degree_to_rad(degree_angle));
	// printf("ray x = %f y = %f\n", ray.x, ray.y);
	return (ray);
}

int	create_trgb_struct(t_color color)
{
	return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}

t_color	extract_rgb(int color_int)
{
	t_color	color;

	color.r = (color_int & 0xFF000000) >> 24;
	color.g = (color_int & 0x00FF0000) >> 16;
	color.b = (color_int & 0x0000FF00) >> 8;
	return (color);
}

int	draw_vertical_slice(t_mlx_img *img, t_cub *cub, int x, double proj_height,
		double distance, double inter_x, double inter_y)
{
	double	start_y;
	double	end_y;
	double	screen_half;
	double	proj_half;
	int		color;
	t_color	full_color;
	double	shading;
	double	scaling_factor;
	double	texture_idx;
	double	texture_x;
	double	modf_var_x;
	double	modf_var_y;
	int		i;

	(void)inter_x;
	(void)inter_y;
	(void)texture_idx;
	(void)color;
	// double	mod_var;
	screen_half = (double)SCREEN_HEIGHT / (double)2;
	proj_half = proj_height / (double)2;
	start_y = screen_half - proj_half;
	end_y = screen_half + proj_half;
	shading = fabs(1 - (distance / 20));
	i = 0;
	// printf("inter x = %f y = %f\n", inter_x, inter_y);
	scaling_factor = (end_y - start_y) / 64;
	// printf("texture px = %f\n", scaling_factor);
	inter_x = modf(inter_x, &modf_var_x);
	if (!inter_x)
		inter_x = modf(inter_y, &modf_var_y);
	texture_x = inter_x * 64;
	if (modf(texture_x, &modf_var_x) > 0.5)
		texture_x = ceil(texture_x);
	else
		texture_x = floor(texture_x);
	// printf("inter_x = %f\n", inter_x);
	// printf("texture x = %f\n", texture_x);
	while (i < SCREEN_HEIGHT)
	{
		// printf("x = %d, i = %d\n", x, i);
		while (i < start_y && i < SCREEN_HEIGHT)
		{
			img_pix_put(img, x, i, create_trgb_struct(cub->c_color));
			i++;
		}
		while (i < end_y && i < SCREEN_HEIGHT)
		{
			// texture_idx =
			// // printf("color = %f\n", distance);
			texture_idx = (i - start_y) / scaling_factor;
			if (modf(texture_idx, &modf_var_y) > 0.5 && texture_idx < 63)
				texture_idx = ceil(texture_idx);
			else
				texture_idx = floor(texture_idx);
			color = *get_pixel_from_img(cub->texture, texture_x, texture_idx);
			full_color = extract_rgb(color);
			color = create_trgb(0, full_color.r * shading, full_color.g
					* shading, full_color.b * shading);
			img_pix_put(img, x, i, color);
			// printf("texture indx = %f\n", texture_idx);
			// printf("texture idx = %f\n", texture_idx);
			// if (distance > 20)
			// 	color = create_trgb(0, 0, 0, 0);
			// else
			// 	color = create_trgb(0, 0, 0, 255 * shading);
			// img_pix_put(img, x, i, color);
			i++;
		}
		img_pix_put(img, x, i, create_trgb_struct(cub->f_color));
		i++;
	}
	return (0);
}

int	shoot_rays(t_mlx_img *img, t_cub *cub, t_vector *map_rays)
{
	double	ray_length;
	int		i;
	double	intersection_x;
	double	intersection_y;
	double	angle;
	double	ray_inc;
	double	distance_to_proj_plane;
	double	proj_height;
	double	relative_angle;

	// t_vector	ray;
	i = SCREEN_WIDTH;
	ray_inc = (double)FOV / (double)SCREEN_WIDTH;
	angle = cub->player.angle - (double)(FOV / 2);
	distance_to_proj_plane = (SCREEN_WIDTH / 5) / tan(degree_to_rad(FOV / 2));
	relative_angle = (double)FOV / (double)2;
	while (i >= 0)
	{
		angle += ray_inc;
		if (angle < 0)
			angle += (double)360;
		else if (angle > 360)
			angle -= (double)360;
		ray_length = find_ray_length(cub, angle, &intersection_x,
				&intersection_y);
		relative_angle -= ray_inc;
		proj_height = distance_to_proj_plane / (ray_length
				* cos(degree_to_rad(relative_angle)));
		map_rays[i] = get_vector_from_length(ray_length, angle);
		draw_vertical_slice(img, cub, i, proj_height, ray_length,
			intersection_x, intersection_y);
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
// 	i = SCREEN_HEIGHT - 1;
// 	// printf("==================\n");
// 	ray_inc = (double)FOV / (SCREEN_WIDTH);
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

int	draw_map_rays(t_mlx_img *img, t_cub *cub, t_vector *map_rays)
{
	int	i;
	int	arr_size;

	i = SCREEN_WIDTH;
	arr_size = get_arr_size(cub->map);
	while (i >= 0)
	{
		draw_ray(img, cub->player.pos, get_pos_from_vector(cub->player.pos,
				map_rays[i]), arr_size);
		i--;
	}
	return (0);
}

int	refresh_raycasting(t_cub *cub)
{
	t_mlx_img	*img;
	t_vector	*map_rays;

	// int			arr_size;
	// arr_size = get_arr_size(cub->map);
	img = init_img(&cub->mlx_data);
	if (!img)
		return (error_exit(NULL), -1);
	// printf("player pos = x %f y %f\n", cub->player.pos.x, cub->player.pos.y);
	map_rays = malloc(sizeof(t_vector) * (SCREEN_WIDTH + 1));
	if (!map_rays)
		return (error_exit(NULL), -1);
	shoot_rays(img, cub, map_rays);
	draw_map(img, cub->map);
	draw_map_rays(img, cub, map_rays);
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
	cub->texture = init_texture(cub, "./src/walkstone.xpm");
	if (!cub->texture)
		return (printf("texture error"), -1);
	start_raycasting(&cub->mlx_data, cub);
	// mlx_key_hook(cub->mlx_data.win_ptr, handle_keyboard_inputs, cub);
	mlx_hook(cub->mlx_data.win_ptr, 2, (1L << 0), handle_keyboard_inputs, cub);
	mlx_loop(cub->mlx_data.mlx_ptr);
	return (0);
}
