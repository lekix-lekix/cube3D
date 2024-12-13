/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/12/13 15:35:10 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	tab_max_width(char **tab)
{
	int	i;
	int	current;
	int	max;

	i = -1;
	max = 0;
	while (tab[++i])
	{
		current = ft_strlen(tab[i]);
		if (current > max)
			max = current;
	}
	return (max);
}

int	main(int ac, char **av)
{
	t_cub	cub;
	t_list	*start;
	int		unit_width;
	int		unit_height;

	init_cub(&cub);
	start_mlx(SCREEN_HEIGHT, SCREEN_WIDTH, &cub);
	parsing(ac, av, &start, &cub);
	init_mov(&cub);
	unit_height = (SCREEN_HEIGHT / 2) / size_tab(cub.map);
	unit_width = (SCREEN_WIDTH / 3) / tab_max_width(cub.map);
	if (unit_height < unit_width)
		cub.map_unit = unit_height;
	else
		cub.map_unit = unit_width;
	mlx_hook(cub.mlx_data.win_ptr, 2, 1L << 0, &handle_keypress, &cub);
	mlx_hook(cub.mlx_data.win_ptr, 3, 1L << 1, &handle_keyrelease, &cub);
	start_raycasting(&cub);
	mlx_loop_hook(cub.mlx_data.mlx_ptr, &check_player_movements, &cub);
	mlx_loop(cub.mlx_data.mlx_ptr);
	free_cub(&cub);
}
