/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:08:52 by inbennou          #+#    #+#             */
/*   Updated: 2024/12/03 14:38:24 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_cub(t_cub *cub)
{
	cub->no_text = NULL;
	cub->so_text = NULL;
	cub->ea_text = NULL;
	cub->we_text = NULL;
    cub->mlx_data.mlx_ptr = NULL;
    cub->mlx_data.win_ptr = NULL;
    cub->sky = NULL;
	cub->map = NULL;
	cub->mov.fwd = false;
	cub->mov.bwd = false;
	cub->mov.strafe_l = false;
	cub->mov.strafe_r = false;
	cub->mov.dir_l = false;
	cub->mov.dir_l = false;
    cub->mov.buffer = 0;
	// cub->c_color = -1;
	// cub->f_color = -1;
}
