/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:01:34 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/16 10:01:37 by sabakar-         ###   ########.fr       */
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
