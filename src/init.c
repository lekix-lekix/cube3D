/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:08:52 by inbennou          #+#    #+#             */
/*   Updated: 2024/12/13 15:41:13 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_mov(t_cub *cub)
{
	cub->mov.buffer = 0;
	cub->mov.fwd = 0;
	cub->mov.bwd = 0;
	cub->mov.strafe_l = 0;
	cub->mov.strafe_r = 0;
	cub->mov.dir_l = 0;
	cub->mov.dir_r = 0;
}

void	init_cub(t_cub *cub)
{
	cub->no_text = NULL;
	cub->so_text = NULL;
	cub->ea_text = NULL;
	cub->we_text = NULL;
	cub->mlx_data.mlx_ptr = NULL;
	cub->mlx_data.win_ptr = NULL;
	cub->sky = NULL;
    cub->sky_bool = false;
	cub->map = NULL;
	cub->mov.fwd = false;
	cub->mov.bwd = false;
	cub->mov.strafe_l = false;
	cub->mov.strafe_r = false;
	cub->mov.dir_l = false;
	cub->mov.dir_l = false;
	cub->mov.buffer = 0;
}
