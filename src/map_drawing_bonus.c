/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:49:33 by kipouliq          #+#    #+#             */
/*   Updated: 2025/01/17 13:47:00 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_block(t_mlx_img *img, t_position *px, char c, t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->map_unit)
	{
		j = -1;
		while (++j < cub->map_unit)
		{
			if (i == 0 || j == 0 || i == cub->map_unit - 1 || j == cub->map_unit
				- 1)
				img_pix_put(img, px->x + i, px->y + j, 0x808080);
			else if (c == '1')
				img_pix_put(img, px->x + i, px->y + j, 0x000000);
		}
	}
}

int	draw_map(t_mlx_img *img, t_cub *cub)
{
	int			i;
	int			j;
	t_position	px;

	i = -1;
	px.y = 10;
	while (cub->map[++i])
	{
		j = -1;
		px.x = 10;
		while (cub->map[i][++j])
		{
			if (!ft_is_space(cub->map[i][j]))
				draw_block(img, &px, cub->map[i][j], cub);
			px.x += cub->map_unit;
		}
		px.y += cub->map_unit;
	}
	return (0);
}
