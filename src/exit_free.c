/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:13:48 by kipouliq          #+#    #+#             */
/*   Updated: 2025/01/23 13:18:06 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	tab_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	destroy_free_texture(t_cub *cub, t_texture *texture)
{
	if (texture->text_img)
	{
		mlx_destroy_image(cub->mlx_data.mlx_ptr, texture->text_img->img_ptr);
		free(texture->text_img);
	}
	if (texture->path)
		free(texture->path);
	free(texture);
}

void	free_textures(t_cub *cub)
{
	if (cub->no_text)
		destroy_free_texture(cub, cub->no_text);
	if (cub->so_text)
		destroy_free_texture(cub, cub->so_text);
	if (cub->ea_text)
		destroy_free_texture(cub, cub->ea_text);
	if (cub->we_text)
		destroy_free_texture(cub, cub->we_text);
	if (cub->sky)
		destroy_free_texture(cub, cub->sky);
	if (cub->door_text)
		destroy_free_texture(cub, cub->door_text);
}

int	quit_cube(t_cub *cub)
{
	free_textures(cub);
	if (cub->mlx_data.win_ptr)
		mlx_destroy_window(cub->mlx_data.mlx_ptr, cub->mlx_data.win_ptr);
	if (cub->mlx_data.mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_data.mlx_ptr);
		free(cub->mlx_data.mlx_ptr);
	}
	if (cub->map)
		tab_free(cub->map);
	exit(1);
	return (0);
}
