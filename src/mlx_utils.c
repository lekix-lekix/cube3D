/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:48:08 by kipouliq          #+#    #+#             */
/*   Updated: 2024/11/22 18:11:26 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_mlx_img	*init_texture(t_cub *cub, char *path)
{
	t_mlx_img	*img;
	int			texture_width;
	int			texture_height;

	img = malloc(sizeof(t_mlx_img));
	if (!img)
		return (error_exit(NULL), NULL);
	img->img_ptr = mlx_xpm_file_to_image(cub->mlx_data.mlx_ptr, path,
			&texture_width, &texture_height);
	if (!img->img_ptr)
		return (error_exit(NULL), NULL);
	img->img_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	return (img);
}

t_mlx_img	*init_img(t_window_mlx *data)
{
	t_mlx_img	*img;

	img = malloc(sizeof(t_mlx_img));
	if (!img)
		return (error_exit(NULL), NULL);
	img->img_ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	if (!img->img_ptr)
		return (NULL);
	img->img_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	return (img);
}

int	*get_pixel_from_img(t_mlx_img *img, int x, int y)
{
	char	*pixel;

	// int		pixel_int;
	pixel = img->img_addr + (y * img->line_len + x * (img->bpp / 8));
	// printf("texture bpp = %d\n", img->bpp);
	// printf("line len = %d\n", img->line_len);
	// printf("img = %s\n", img->img_addr);
	return ((int *)pixel);
}

void	img_pix_put(t_mlx_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->img_addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
