/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:44:36 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/28 11:45:11 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_character_up(t_cub *cub)
{
    cub->player.pos.y -= 0.1;
    refresh_raycasting(cub);
    return (0);
}

int	move_character_down(t_cub *cub)
{
    cub->player.pos.y += 0.1;
    refresh_raycasting(cub);
    return (0);
}

int	move_character_left(t_cub *cub)
{
    cub->player.pos.x -= 0.1;
    refresh_raycasting(cub);
    return (0);
}

int	move_character_right(t_cub *cub)
{
    cub->player.pos.x += 0.1;
    refresh_raycasting(cub);
    return (0);
}
