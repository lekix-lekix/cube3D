/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:39:12 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/12 13:47:37 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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
