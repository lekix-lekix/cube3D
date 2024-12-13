/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:36:52 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/12 16:28:51 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_start_end_y_px(t_ray *ray, t_cub *cub, t_position *start_end_px,
		t_texture_slice *slice)
{
	start_end_px->x = ((double)SCREEN_HEIGHT / (double)2) - (ray->proj_height
			/ (double)2);
	if (start_end_px->x > SCREEN_HEIGHT)
		start_end_px->x = 0;
	start_end_px->y = ((double)SCREEN_HEIGHT / (double)2) + (ray->proj_height
			/ (double)2);
	if (start_end_px->y > SCREEN_HEIGHT)
		start_end_px->y = SCREEN_HEIGHT - 1;
	pick_texture_slice(cub, ray, slice);
	slice->scaling = ray->proj_height / slice->texture->height;
}

int	draw_vertical_slice(t_mlx_img *img, t_cub *cub, int x, t_ray *ray)
{
	t_position		start_end_px;
	t_texture_slice	slice;
	int				color;
	int				i;

	i = -1;
	init_start_end_y_px(ray, cub, &start_end_px, &slice);
	while (++i < SCREEN_HEIGHT - 1)
	{
		if (i < start_end_px.x)
		{
			if (cub->sky_bool)
				color = *get_pixel_from_img(cub->sky->text_img, x, i);
			else
				color = create_trgb_struct(cub->c_color);
		}
		else if (i < start_end_px.y)
			color = pick_slice_color(&slice, ray, i, start_end_px.x);
		else
			color = create_trgb_struct(cub->f_color);
		img_pix_put(img, x, i, color);
	}
	return (0);
}
