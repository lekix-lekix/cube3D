/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/11/29 17:32:58 by kipouliq         ###   ########.fr       */
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

	arr_size = get_arr_size(cub->map);
	fov_l = get_pos_from_vector(cub->player.pos, cub->player.fov_l);
	fov_r = get_pos_from_vector(cub->player.pos, cub->player.fov_r);
	dir = get_pos_from_vector(cub->player.pos, cub->player.dir);
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
	cub->sky = init_mlx_img_texture(cub, "./textures/sky_big.xpm");
	if (!cub->sky)
		return (error_exit(NULL), -1);
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

void	init_dx_dy(t_dda_vars *vars, double angle)
{
	if (angle == 360)
		(*vars).dy = INFINITY;
	else
		(*vars).dy = fabs(1 / fabs(sin(degree_to_rad(angle))));
	if (angle == 90)
		(*vars).dx = INFINITY;
	else
		(*vars).dx = fabs(1 / fabs(cos(degree_to_rad(angle))));
}

void	init_dx_dy_sums(t_dda_vars *vars, t_position player_pos, double angle)
{
	double	modf_var;
	double	modf_real;

	modf_real = modf(player_pos.x, &modf_var);
	if (modf_real)
	{
		if (angle < 90 || angle > 270)
			(*vars).dx_sum = fabs((1 - modf_real) * (*vars).dx);
		else
			(*vars).dx_sum = fabs(modf_real * (*vars).dx);
	}
	else
		(*vars).dx_sum = fabs((*vars).dx);
	if (modf(player_pos.y, &modf_var))
	{
		modf_real = modf(player_pos.y, &modf_var);
		if (angle > 180)
			(*vars).dy_sum = fabs((1 - modf_real) * (*vars).dy);
		else
			(*vars).dy_sum = fabs(modf_real * (*vars).dy);
	}
	else
		(*vars).dy_sum = fabs((*vars).dy);
}

double	wall_hit(t_ray *ray, t_position player_pos, t_dda_vars vars,
		int last_inc)
{
	if (last_inc == 0)
	{
		(*ray).intersection_x = player_pos.x + cos(degree_to_rad((*ray).angle))
			* (vars.dy_sum - vars.dy);
		(*ray).intersection_y = vars.y;
		return (fabs(vars.dy_sum - vars.dy));
	}
	else
	{
		(*ray).intersection_x = vars.x;
		(*ray).intersection_y = player_pos.y - (sin(degree_to_rad((*ray).angle))
				* (vars.dx_sum - vars.dx));
		return (fabs(vars.dx_sum - vars.dx));
	}
}

int	inc_dx_sum(t_dda_vars *vars, t_ray *ray)
{
	if ((*ray).angle > 180 && (*ray).angle <= 359)
		(*vars).y++;
	else
		(*vars).y--;
	(*vars).dy_sum += (*vars).dy;
	return (0);
}

int	inc_dy_sum(t_dda_vars *vars, t_ray *ray)
{
	if ((*ray).angle > 90 && (*ray).angle <= 270)
		(*vars).x--;
	else
		(*vars).x++;
	(*vars).dx_sum += (*vars).dx;
	return (1);
}

double	find_ray_length(t_cub *cub, t_ray *ray)
{
	t_dda_vars	dda_vars;
	int			last_inc;

	init_dx_dy(&dda_vars, (*ray).angle);
	init_dx_dy_sums(&dda_vars, cub->player.pos, (*ray).angle);
	last_inc = -1;
	dda_vars.x = cub->player.pos.x;
	dda_vars.y = cub->player.pos.y;
	while (dda_vars.x >= 0 && dda_vars.y >= 0)
	{
		if (cub->map[dda_vars.y][dda_vars.x] == '1')
			return (wall_hit(ray, cub->player.pos, dda_vars, last_inc));
		if (dda_vars.dx_sum > dda_vars.dy_sum)
			last_inc = inc_dx_sum(&dda_vars, ray);
		else
			last_inc = inc_dy_sum(&dda_vars, ray);
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

void	pick_texture_slice(t_cub *cub, t_ray *ray, t_texture_slice *slice)
{
	double	modf_var_x;
	double	modf_var_y;

	(*ray).intersection_x = modf((*ray).intersection_x, &modf_var_x);
	if (!ray->intersection_x)
	{
		(*ray).intersection_x = modf((*ray).intersection_y, &modf_var_y);
		if ((*ray).angle >= 90 && (*ray).angle <= 270)
			slice->texture = cub->we_text;
		else
			slice->texture = cub->ea_text;
	}
	else
	{
		if ((*ray).angle >= 180 && (*ray).angle <= 360)
			slice->texture = cub->so_text;
		else
			slice->texture = cub->no_text;
	}
	slice->idx_x = ray->intersection_x * slice->texture->width;
	if (modf(slice->idx_x, &modf_var_x) > 0.5)
		slice->idx_x = ceil(slice->idx_x);
	else
		slice->idx_x = floor(slice->idx_x);
}

int	create_shaded_color(t_ray *ray, t_color color)
{
	double	shading;

	if (ray->length > 20)
		return (create_rgb(0, 0, 0));
	shading = fabs(1 - ((*ray).length / 20));
	return (create_trgb(0, color.r * shading, color.g * shading, color.b
			* shading));
}

int	pick_slice_color(t_texture_slice *slice, t_ray *ray, int i, int start_y_px)
{
	double	modf_var_y;
	int		color;

	(*slice).idx_y = (i - start_y_px) / (*slice).scaling;
	if (modf((*slice).idx_y, &modf_var_y) > 0.5 && (*slice).idx_y < 63)
		(*slice).idx_y = ceil((*slice).idx_y);
	else
		(*slice).idx_y = floor((*slice).idx_y);
	if ((*slice).idx_x >= (*slice).texture->width)
		(*slice).idx_x = (*slice).texture->width - 1;
	if ((*slice).idx_y >= (*slice).texture->height)
		(*slice).idx_y = (*slice).texture->height - 1;
	color = *get_pixel_from_img((*slice).texture->text_img, (*slice).idx_x,
			(*slice).idx_y);
	return (create_shaded_color(ray, extract_rgb(color)));
}

int	draw_vertical_slice(t_mlx_img *img, t_cub *cub, int x, double proj_height,
		t_ray ray)
{
	double			start_y_px;
	double			end_y_px;
	t_texture_slice	slice;
	int				color;
	int				i;

	start_y_px = ((double)SCREEN_HEIGHT / (double)2) - (proj_height
			/ (double)2);
	end_y_px = ((double)SCREEN_HEIGHT / (double)2) + (proj_height / (double)2);
	pick_texture_slice(cub, &ray, &slice);
	slice.scaling = proj_height / slice.texture->height;
	i = -1;
	while (++i < SCREEN_HEIGHT)
	{
		while (i < start_y_px && i < SCREEN_HEIGHT)
		{
			img_pix_put(img, x, i, *get_pixel_from_img(cub->sky->text_img, x,
					i));
			// img_pix_put(img, x, i, create_trgb_struct(cub->c_color));
			i++;
		}
		while (i < end_y_px && i < SCREEN_HEIGHT - 1)
		{
			color = pick_slice_color(&slice, &ray, i, start_y_px);
			img_pix_put(img, x, i, color);
			i++;
		}
		img_pix_put(img, x, i, create_trgb_struct(cub->f_color));
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

int check_player_movements(t_cub *cub)
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
    // check_player_movements(cub);
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
