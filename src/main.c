/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:20:15 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/16 13:08:15 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
int	ft_parsing (char *file_path, t_cub *cub);

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

// Free resources
void	ft_destroy_cub(t_cub cub)
{
	mlx_destroy_window(cub.mlx_data.mlx_ptr, cub.mlx_data.win_ptr);
	mlx_destroy_display(cub.mlx_data.mlx_ptr);
	free(cub.mlx_data.mlx_ptr);
}

int	main(int ac, char **av)
{
	t_cub	cub;
	int		unit_width;
	int		unit_height;

	if (ac != 2)
		return (printf("Dude, give it a map.\n"), 1);
	init_cub(&cub);
	printf("The return was: %d\n", start_mlx(SCREEN_HEIGHT, SCREEN_WIDTH, &cub));
	if (!ft_parsing(av[1], &cub))
		return (ft_destroy_cub(cub), 1);
	init_mov(&cub);
	unit_height = (SCREEN_HEIGHT / 2) / size_tab(cub.map);
	unit_width = (SCREEN_WIDTH / 3) / tab_max_width(cub.map);
	if (unit_height < unit_width)
		cub.map_unit = unit_width;
	else
		cub.map_unit = unit_height;
	mlx_hook(cub.mlx_data.win_ptr, 2, 1L << 0, &handle_keypress, &cub);
	mlx_hook(cub.mlx_data.win_ptr, 3, 1L << 1, &handle_keyrelease, &cub);
	mlx_hook(cub.mlx_data.win_ptr, 17, 1L << 17, &handle_destroy, &cub);
	start_raycasting(&cub);
	mlx_loop_hook(cub.mlx_data.mlx_ptr, &check_player_movements, &cub);
	mlx_loop(cub.mlx_data.mlx_ptr);
}

int	ft_parsing (char *file_path, t_cub *cub)
{
	if (!ft_check_extension(file_path))
		return (0);
	if (!ft_read_file(file_path, cub))
		return (0);
	check_map(cub);
	return (1);
}
