/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/11/26 18:24:26 by kipouliq         ###   ########.fr       */
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

int	start_raycasting(t_cub *cub)
{
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
	return (0);
}

double	find_ray_length(t_cub *cub, t_ray *ray)
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

	if ((*ray).angle == 360)
		dy = INFINITY;
	else
		dy = fabs(1 / fabs(sin(degree_to_rad((*ray).angle))));
	if ((*ray).angle == 90)
		dx = INFINITY;
	else
		dx = fabs(1 / fabs(cos(degree_to_rad((*ray).angle))));
	x = cub->player.pos.x;
	y = cub->player.pos.y;
	if (modf(cub->player.pos.x, &modf_var))
	{
		if (modf(cub->player.pos.x, &modf_var))
		{
			modf_real = modf(cub->player.pos.x, &modf_var);
			if ((*ray).angle < 90 || (*ray).angle > 270)
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
			if ((*ray).angle > 180)
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
				(*ray).intersection_x = cub->player.pos.x
					+ cos(degree_to_rad((*ray).angle)) * (dy_sum - dy);
				(*ray).intersection_y = y;
				return (ray_length);
			}
			else
			{
				ray_length = fabs(dx_sum - dx);
				(*ray).intersection_x = x;
				(*ray).intersection_y = cub->player.pos.y
					- (sin(degree_to_rad((*ray).angle)) * (dx_sum - dx));
				return (ray_length);
			}
			return (ray_length);
		}
		if (dx_sum > dy_sum)
		{
			if ((*ray).angle > 180 && (*ray).angle <= 359)
				y++;
			else
				y--;
			dy_sum += dy;
			last_inc = 0;
		}
		else
		{
			if ((*ray).angle > 90 && (*ray).angle <= 270)
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

	color.r = (color_int & 0x00FF0000) >> 16;
	color.g = (color_int & 0x0000FF00) >> 8;
	color.b = (color_int & 0x000000FF) >> 0;
	return (color);
}

t_texture	*pick_texture(t_cub *cub, double angle, char wall)
{
	if (wall == 'H')
	{
		if (angle >= 180 && angle <= 360 && wall == 'H')
			return (cub->no_text);
		else
			return (cub->so_text);
	}
	else
	{
		if (angle >= 90 && angle <= 270)
			return (cub->we_text);
		else
			return (cub->ea_text);
	}
}

// int	draw_vertical_slice(t_mlx_img *img, t_cub *cub, int x,
// double proj_height,
// double distance, double inter_x, double inter_y, int angle)
int	draw_vertical_slice(t_mlx_img *img, t_cub *cub, int x, double proj_height,
		t_ray ray)
{
	double		start_y;
	double		end_y;
	double		screen_half;
	double		proj_half;
	int			color;
	t_color		full_color;
	double		shading;
	double		scaling_factor;
	double		texture_idx;
	double		texture_x;
	double		modf_var_x;
	double		modf_var_y;
	t_texture	*texture;
	char		wall;
	int			i;

	screen_half = (double)SCREEN_HEIGHT / (double)2;
	proj_half = proj_height / (double)2;
	start_y = screen_half - proj_half;
	end_y = screen_half + proj_half;
	shading = fabs(1 - (ray.length / 20));
	i = 0;
	scaling_factor = (end_y - start_y) / 64;
	ray.intersection_x = modf(ray.intersection_x, &modf_var_x);
	if (!ray.intersection_x)
	{
		ray.intersection_x = modf(ray.intersection_y, &modf_var_y);
		wall = 'V';
	}
	else
		wall = 'H';
	texture_x = ray.intersection_x * 64;
	if (modf(texture_x, &modf_var_x) > 0.5)
		texture_x = ceil(texture_x);
	else
		texture_x = floor(texture_x);
	while (i < SCREEN_HEIGHT)
	{
		while (i < start_y && i < SCREEN_HEIGHT)
		{
			img_pix_put(img, x, i, create_trgb_struct(cub->c_color));
			i++;
		}
		while (i < end_y && i < SCREEN_HEIGHT)
		{
			texture_idx = (i - start_y) / scaling_factor;
			if (modf(texture_idx, &modf_var_y) > 0.5 && texture_idx < 63)
				texture_idx = ceil(texture_idx);
			else
				texture_idx = floor(texture_idx);
			texture = pick_texture(cub, ray.angle, wall);
			color = *get_pixel_from_img(texture->text_img, texture_x,
					texture_idx);
			full_color = extract_rgb(color);
			color = create_trgb(0, full_color.r * shading, full_color.g
					* shading, full_color.b * shading);
			img_pix_put(img, x, i, color);
			i++;
		}
		img_pix_put(img, x, i, create_trgb_struct(cub->f_color));
		i++;
	}
	return (0);
}

t_ray	init_ray(double player_angle)
{
	t_ray	ray;

	ray.angle_inc = (double)FOV / (double)SCREEN_WIDTH;
	ray.angle = player_angle - (double)(FOV / 2);
	ray.distance_to_proj_plane = (SCREEN_WIDTH / 5) / tan(degree_to_rad(FOV
				/ 2));
	ray.relative_angle = (double)FOV / (double)2;
	return (ray);
}

int	shoot_rays(t_mlx_img *img, t_cub *cub, t_vector *map_rays)
{
	t_ray	ray;
	int		i;

	i = SCREEN_WIDTH;
	ray = init_ray(cub->player.angle);
	while (i >= 0)
	{
		ray.angle += ray.angle_inc;
		if (ray.angle < 0)
			ray.angle += (double)360;
		else if (ray.angle > 360)
			ray.angle -= (double)360;
		ray.length = find_ray_length(cub, &ray);
		ray.relative_angle -= ray.angle_inc;
		ray.proj_height = ray.distance_to_proj_plane / (ray.length
				* cos(degree_to_rad(ray.relative_angle)));
		map_rays[i] = get_vector_from_length(ray.length, ray.angle);
		draw_vertical_slice(img, cub, i, ray.proj_height, ray);
		i--;
	}
	return (0);
}

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

	img = init_img(&cub->mlx_data);
	if (!img)
		return (error_exit(NULL), -1);
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
	return (0);
}
