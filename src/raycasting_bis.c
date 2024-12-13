/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:23:07 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/12 12:35:41 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	inc_dx_sum(t_dda_vars *vars, t_ray *ray)
{
	if ((*ray).angle > 180 && (*ray).angle <= 360)
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
		if (cub->map[dda_vars.y][dda_vars.x] == '1'
			|| cub->map[dda_vars.y][dda_vars.x] == 'D')
			return (wall_hit(ray, cub->player.pos, dda_vars, last_inc));
		if (dda_vars.dx_sum > dda_vars.dy_sum)
			last_inc = inc_dx_sum(&dda_vars, ray);
		else
			last_inc = inc_dy_sum(&dda_vars, ray);
	}
	return (-1);
}
