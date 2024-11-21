/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/11/21 15:07:15 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;
    t_list  *start;

	parsing(ac, av, &start, &cub);
	// printf("c-color = %d et f_color = %d\n", cub.c_color, cub.f_color);
	// printf("cub %s %s %s %s %d %d\n", cub.no_text, cub.so_text, cub.ea_text,
		// cub.we_text, cub.c_color, cub.f_color);
    print_tab(cub.map);
    start_mlx(SCREEN_HEIGHT, SCREEN_WIDTH, &cub);
	free_cub(&cub);
}
