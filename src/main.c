/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/11/26 14:13:30 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	mlx_hook(cub.mlx_data.win_ptr, 2, (1L << 0), handle_keyboard_inputs, &cub);
	mlx_loop(cub.mlx_data.mlx_ptr);
	free_cub(&cub);
}
