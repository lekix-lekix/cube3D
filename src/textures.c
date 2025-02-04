/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:55:12 by kipouliq          #+#    #+#             */
/*   Updated: 2025/02/04 15:41:40 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	pick_door_texture(t_cub *cub, t_ray *ray, t_texture_slice *slice)
{
	double	modf_var;

	slice->texture = cub->door_text;
	(*ray).intersection_x = modf((*ray).intersection_x, &modf_var);
	if (!(*ray).intersection_x)
		(*ray).intersection_x = modf((*ray).intersection_y, &modf_var);
	slice->idx_x = round(ray->intersection_x * (double)slice->texture->width);
}

void	pick_texture_slice(t_cub *cub, t_ray *ray, t_texture_slice *slice)
{
	double	modf_var;

	if (cub->map[(int)(*ray).intersection_y][(int)(*ray).intersection_x] == 'D')
	{
		pick_door_texture(cub, ray, slice);
		return ;
	}
	(*ray).intersection_x = modf((*ray).intersection_x, &modf_var);
	if (!ray->intersection_x)
	{
		(*ray).intersection_x = modf((*ray).intersection_y, &modf_var);
		if ((*ray).angle >= 90 && (*ray).angle <= 270)
			slice->texture = cub->we_text;
		else
			slice->texture = cub->ea_text;
	}
	else
	{
		if ((*ray).angle >= 180 && (*ray).angle <= 360)
			slice->texture = cub->no_text;
		else
			slice->texture = cub->so_text;
	}
	slice->idx_x = round(ray->intersection_x * (double)slice->texture->width);
}

int	pick_slice_color(t_texture_slice *slice, t_ray *ray, int i, int start_y_px)
{
	int	color;

	(*slice).idx_y = (i - start_y_px) / (*slice).scaling;
	(*slice).idx_y = round((*slice).idx_y);
	if ((*slice).idx_x >= (*slice).texture->width)
		(*slice).idx_x = (*slice).texture->width - 1;
	if ((*slice).idx_y >= (*slice).texture->height)
		(*slice).idx_y = (*slice).texture->height - 1;
	if ((*slice).idx_y < 0)
		(*slice).idx_y = 0;
	color = *get_pixel_from_img((*slice).texture->text_img, (*slice).idx_x,
			(*slice).idx_y);
	return (create_shaded_color(ray, extract_rgb(color)));
}
