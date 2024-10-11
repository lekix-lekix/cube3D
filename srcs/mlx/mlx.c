/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/11 17:48:11 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

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

void	img_pix_put(t_mlx_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->img_addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	start_raycasting(t_window_mlx *data)
{
	t_mlx_img	*img;

	img = init_img(data);
	if (!img)
		return (error_exit(NULL), -1);
	img_pix_put(img, 100, 100, 0xFF0000);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int	start_mlx(int height, int width)
{
	t_window_mlx	data;

	data.mlx_ptr = mlx_init();
	data.width = width;
	data.height = height;
	if (!data.mlx_ptr)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, width, height, "cube3D");
	if (!data.win_ptr)
		return (-1);
	start_raycasting(&data);
    mlx_hook(data.win_ptr, 2, (1L << 0), handle_keyboard_input, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
