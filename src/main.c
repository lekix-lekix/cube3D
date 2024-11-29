/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/11/29 17:24:39 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handle_keypress(int key, t_cub *cub)
{
	printf("keypress key = %d\n", key);
	// if (cub->mov.buffer == 0)
	    // cub->mov.buffer = key;
	// printf("buffer = %d\n", cub->mov.buffer);
	if (cub->mov.buffer == W)
	{
		if (!cub->mov.fwd)
			cub->mov.fwd = true;
		if (cub->mov.bwd)
			cub->mov.bwd = false;
	}
	if (cub->mov.buffer == S)
	{
		if (!cub->mov.bwd)
			cub->mov.bwd = true;
		if (cub->mov.fwd)
			cub->mov.fwd = false;
	}
	if (cub->mov.buffer == A)
	{
		if (!cub->mov.strafe_l)
			cub->mov.strafe_l = true;
		if (cub->mov.strafe_r)
			cub->mov.strafe_r = false;
	}
	if (cub->mov.buffer == D)
	{
		if (!cub->mov.strafe_r)
			cub->mov.strafe_r = true;
		if (cub->mov.strafe_l)
			cub->mov.strafe_l = false;
	}
	if (cub->mov.buffer == LEFT)
	{
		if (!cub->mov.dir_l)
			cub->mov.dir_l = true;
		if (cub->mov.dir_r)
			cub->mov.dir_r = false;
	}
	if (cub->mov.buffer == RIGHT)
	{
		if (!cub->mov.dir_r)
			cub->mov.dir_r = true;
		if (cub->mov.dir_l)
			cub->mov.dir_l = false;
	}
	return (0);
}

int	handle_keyrelease(int key, t_cub *cub)
{
    (void) cub;
    printf("key = %d\n", key);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;
	t_list	*start;

	start_mlx(SCREEN_HEIGHT, SCREEN_WIDTH, &cub);
	parsing(ac, av, &start, &cub);
	// printf("c-color = %d et f_color = %d\n", cub.c_color, cub.f_color);
	// printf("cub %s %s %s %s %d %d\n", cub.no_text, cub.so_text, cub.ea_text,
	// cub.we_text, cub.c_color, cub.f_color);
	print_tab(cub.map);
	start_raycasting(&cub);
	// mlx_hook(cub.mlx_data.win_ptr, 2, 1L << 0, handle_keypress, &cub)
	// mlx_hook(cub.mlx_data.win_ptr, 3, 1L << 1, handle_keyrelease, &cub);
	mlx_loop(cub.mlx_data.mlx_ptr);
	free_cub(&cub);
}
