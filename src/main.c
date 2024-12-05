/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/12/05 15:43:39 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handle_keypress(int key, t_cub *cub)
{
	if (key == ESCAPE)
		quit_cube(cub);
	if (cub->mov.buffer == 0 || cub->mov.buffer != key)
		cub->mov.buffer = key;
	if (cub->mov.buffer == W)
		cub->mov.fwd = true;
	else if (cub->mov.buffer == S)
		cub->mov.bwd = true;
	else if (cub->mov.buffer == A)
		cub->mov.strafe_l = true;
	else if (cub->mov.buffer == D)
		cub->mov.strafe_r = true;
	else if (cub->mov.buffer == LEFT)
		cub->mov.dir_l = true;
	else if (cub->mov.buffer == RIGHT)
		cub->mov.dir_r = true;
	return (0);
}

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

int	handle_keyrelease(int key, t_cub *cub)
{
	if (key == cub->mov.buffer)
		cub->mov.buffer = 0;
	if (key == W)
		cub->mov.fwd = 0;
	else if (key == S)
		cub->mov.bwd = 0;
	else if (key == A)
		cub->mov.strafe_l = 0;
	else if (key == D)
		cub->mov.strafe_r = 0;
	else if (key == LEFT)
		cub->mov.dir_l = 0;
	else if (key == RIGHT)
		cub->mov.dir_r = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;
	t_list	*start;

	init_cub(&cub);
	start_mlx(SCREEN_HEIGHT, SCREEN_WIDTH, &cub);
	parsing(ac, av, &start, &cub);
	init_mov(&cub);
	print_tab(cub.map);
	mlx_hook(cub.mlx_data.win_ptr, 2, 1L << 0, &handle_keypress, &cub);
	mlx_hook(cub.mlx_data.win_ptr, 3, 1L << 1, &handle_keyrelease, &cub);
    // mlx_hook(cub.mlx_data.win_ptr, 2, 1L << 0, handle_keyboard_inputs, &cub);
	start_raycasting(&cub);
	mlx_loop_hook(cub.mlx_data.mlx_ptr, &check_player_movements, &cub);
	mlx_loop(cub.mlx_data.mlx_ptr);
	free_cub(&cub);
}
