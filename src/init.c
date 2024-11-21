/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:08:52 by inbennou          #+#    #+#             */
/*   Updated: 2024/11/21 15:06:38 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_cub(t_cub *cub)
{
	cub->no_text = NULL;
	cub->so_text = NULL;
	cub->ea_text = NULL;
	cub->we_text = NULL;
	cub->map = NULL;
	// cub->c_color = -1;
	// cub->f_color = -1;
}
