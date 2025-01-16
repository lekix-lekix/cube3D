/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:48:08 by kipouliq          #+#    #+#             */
/*   Updated: 2025/01/16 18:32:04 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int start_mlx(int height, int width, t_cub *cub)
{
	cub->mlx_data.mlx_ptr = mlx_init();
	if (!cub->mlx_data.mlx_ptr)
		return (printf("We are indeed here\n"), error_exit(MEM_ERROR, cub), -1);
	cub->mlx_data.width = width;
	cub->mlx_data.height = height;
	cub->mlx_data.win_ptr = mlx_new_window(cub->mlx_data.mlx_ptr, width, height,
										   "cub3D");
	if (!cub->mlx_data.win_ptr)
		return (error_exit(MEM_ERROR, cub), -1);
	return (0);
}

void init_mlx_img_texture(t_cub *cub, t_texture *text)
{
	text->text_img = malloc(sizeof(t_mlx_img));
	if (!text->text_img)
		error_exit(NULL, cub);
	text->text_img->img_ptr = mlx_xpm_file_to_image(cub->mlx_data.mlx_ptr,
													text->path, &text->width, &text->height);
	if (!text->text_img->img_ptr)
		error_exit(NULL, cub);
	text->text_img->img_addr = mlx_get_data_addr(text->text_img->img_ptr,
												 &text->text_img->bpp, &text->text_img->line_len,
												 &text->text_img->endian);
}

t_mlx_img *init_img(t_window_mlx *data, t_cub *cub)
{
	t_mlx_img *img;

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

int *get_pixel_from_img(t_mlx_img *img, int x, int y)
{
	char *pixel;

	pixel = img->img_addr + (y * img->line_len + x * (img->bpp / 8));
	return ((int *)pixel);
}

void img_pix_put(t_mlx_img *img, int x, int y, int color)
{
	char *pixel;

	pixel = img->img_addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
