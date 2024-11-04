/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/11/04 17:46:46 by kipouliq         ###   ########.fr       */
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

// int shoot_rays(t_cub *cub)
// {
//     t_vector *rays;
//     t_position fov_l;
//     t_position fov_r;

//     rays = malloc(sizeof(t_vector) * 10);
//     if (!rays)
//         return (error_exit(NULL));
//     fov_l = get_pos_from_vector(cub->player.pos, cub->player.fov_l);
//     fov_r = get_pos_from_vector(cub->player.pos, cub->player.fov_r);
//     return (0);
// }

// int	draw_ray(t_mlx_img *img, t_position start, t_vector end, int arr_size,
// int color)
// {
//     t_position ray_start;
//     t_position ray_end;

//     // ray_end = get_pos_from_vector(start, end);
//     // start = coordinates_to_px(start.x, start.y, arr_size);
//     // start.x = round(start.x);
//     // start.y = round(start.y);
//     // ray_end = coordinates_to_px(end.x + start.x, end.y + start.y,
// arr_size);
//     // ray_end.x = round(ray_end.x);
//     // ray_end.y = round(ray_end.y);
//     ray_start = coordinates_to_px(start.x, start.y, arr_size);
//     // ray_start.x = round(ray_start.x);
//     // ray_start.y = round(ray_start.y);
//     ray_end = get_pos_from_vector(start, end);
//     printf("player px pos = x %f y %f\n", ray_start.x, ray_start.y);
//     printf("ray_end vector position x %f y %f\n", ray_end.x, ray_end.y);
//     ray_end = coordinates_to_px(ray_end.x, ray_end.y, arr_size);
//     // ray_end.x = round(ray_end.x);
//     // ray_end.y = round(ray_end.y);
//     printf("ray_end x = %f ray_end y = %f\n", ray_end.x, ray_end.y);
// 	if (abs((int)ray_end.x > (int)ray_start.x) > abs((int)ray_end.y
// - (int)ray_start.y))
// 		draw_ray_horizontal(img, ray_start, ray_end, color);
// 	else
// 		draw_ray_vertical(img, ray_start, ray_end, color);
//     printf("==========\n");
// 	return (0);
// }

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
	draw_map(img, cub->map);
	cub->player.dir = find_dir(cub);
	if (cub->player.initial_dir == 'N')
		cub->player.angle = 90;
	else if (cub->player.initial_dir == 'E')
		cub->player.angle = 360;
	else if (cub->player.initial_dir == 'S')
		cub->player.angle = 270;
	else
		cub->player.angle = 180;
	// init_camera_vectors(cub);
	// draw_player(img, cub);
	refresh_raycasting(cub);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0,
	// 0);
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

	// printf("pos x = %f y = %f\n", cub->player.pos.x, cub->player.pos.y);
	printf("angle is %f\n", degree_ray_angle);
	dy = fabs(1 / fabs(sin(degree_to_rad(degree_ray_angle))));
	dx = fabs(1 / fabs(cos(degree_to_rad(degree_ray_angle))));
	// printf("dx = %f, dy = %f\n", dx, dy);
	x = cub->player.pos.x;
	y = cub->player.pos.y;
	// printf("modf = %f\n", modf(cub->player.pos.x, &modf_var));
	// printf("dx sum calc = %f\n", cos(degree_to_rad(degree_ray_angle)));
	if (modf(cub->player.pos.x, &modf_var))
	{
		modf_real = modf(cub->player.pos.x, &modf_var);
		if (degree_ray_angle < 90)
			dx_sum = fabs((1 - modf_real) * dx);
		else
			dx_sum = fabs(modf_real * dx);
	}
	else
		dx_sum = fabs(dx);
	if (modf(cub->player.pos.y, &modf_var))
	{
		modf_real = modf(cub->player.pos.y, &modf_var);
		if (degree_ray_angle > 180 && degree_ray_angle <= 359)
			dy_sum = fabs((1 + modf_real) * dy);
		dy_sum = fabs(modf_real * dy);
	}
	else
		dy_sum = fabs(dy);
	// printf("init dx sum = %f, dy sum = %f\n", dx_sum, dy_sum);
	wall_hit = 0;
	last_inc = -1;
	while (!wall_hit && x >= 0 && y >= 0)
	{
		// printf("top of the loop = x = %d, y = %d\n", x, y);
		if (cub->map[y][x] == '1')
		{
			// printf("wall check = x %d y %d\n", x, y);
			if (last_inc == 0)
				ray_length = fabs(dy_sum - dy);
			if (last_inc == 1)
				ray_length = fabs(dx_sum - dx);
			// printf("wall hit at x %d y %d\n", x, y);
			// printf("ray lenght = %f\n", ray_length);
			return (ray_length);
		}
		if (dx_sum > dy_sum)
		{
			// printf("x is smaller dx sum = %f\n", dx_sum);
			y--;
			dy_sum += dy;
			last_inc = 0;
		}
		else
		{
			// printf("y is smaller dy sum = %f\n", dy_sum);
			if (degree_ray_angle > 90)
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

double	calculate_ray_angle(double player_angle, double ray_angle)
{
}

int	shoot_rays(t_mlx_img *img, t_cub *cub)
{
	int			arr_size;
	t_vector	ray;
	double		ray_length;
	int			i;
	double		angle;
	double		ray_inc;

	arr_size = get_arr_size(cub->map);
	i = 0;
	printf("==================\n");
	ray_inc = FOV / 20;
    angle = FOV - (FOV / 2);
	while (i < 20)
	{
        
		ray_length = find_ray_length(cub, angle);
		ray = get_vector_from_length(ray_length, angle);
		draw_ray(img, cub->player.pos, get_pos_from_vector(cub->player.pos,
				ray), arr_size);
		i++;
	}
	return (0);
}

int	refresh_raycasting(t_cub *cub)
{
	t_mlx_img	*img;
	int			arr_size;

	arr_size = get_arr_size(cub->map);
	img = init_img(&cub->mlx_data);
	if (!img)
		return (error_exit(NULL), -1);
	printf("player pos = x %f y %f\n", cub->player.pos.x, cub->player.pos.y);
	draw_map(img, cub->map);
	shoot_rays(img, cub);
	// draw_player(img, cub);
	// draw_ray(img, cub->player.pos, get_pos_from_vector(cub->player.pos,
	// cub->player.fov_l), arr_size);
	// draw_ray(img, cub->player.pos, get_pos_from_vector(cub->player.pos,
	// cub->player.fov_r), arr_size);
	// draw_ray(img, cub->player.pos, get_pos_from_vector(cub->player.pos,
	// cub->player.dir), arr_size);
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
