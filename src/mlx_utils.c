/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:48:08 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/03 12:45:22 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_texture	*init_mlx_img_texture(t_cub *cub, char *path)
{
	t_texture	*texture;
	int			texture_width;
	int			texture_height;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (error_exit(NULL, cub), NULL);
	texture->text_img = malloc(sizeof(t_mlx_img));
	if (!texture->text_img)
		return (error_exit(NULL, cub), NULL);
	texture->text_img->img_ptr = mlx_xpm_file_to_image(cub->mlx_data.mlx_ptr,
			path, &texture_width, &texture_height);
	if (!texture->text_img->img_ptr)
		return (error_exit(NULL, cub), NULL);
	texture->text_img->img_addr = mlx_get_data_addr(texture->text_img->img_ptr,
			&texture->text_img->bpp, &texture->text_img->line_len,
			&texture->text_img->endian);
    texture->width = texture_width;
    texture->height = texture_height;
	return (texture);
}

t_mlx_img	*init_img(t_window_mlx *data, t_cub *cub)
{
	t_mlx_img	*img;

	img = malloc(sizeof(t_mlx_img));
	if (!img)
		return (error_exit(NULL, cub), NULL);
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

	pixel = img->img_addr + (y * img->line_len + x * (img->bpp / 8));
	return ((int *)pixel);
}

void	img_pix_put(t_mlx_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->img_addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
