/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/12 14:42:55 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_vector	get_vector_from_length(double ray_length, double degree_angle)
{
	t_vector	ray;

	ray.x = 0;
	ray.y = 0;
	ray.x += ray_length * cos(degree_to_rad(degree_angle));
	ray.y -= ray_length * sin(degree_to_rad(degree_angle));
	return (ray);
}
