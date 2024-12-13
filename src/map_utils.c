/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:04:59 by kipouliq          #+#    #+#             */
/*   Updated: 2024/12/12 15:31:12 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	skip_elements(t_list **file_content)
{
	int	i;

	i = 0;
	while (file_content && i < 6)
	{
		if (!is_empty((*file_content)->content))
			i++;
		*file_content = (*file_content)->next;
	}
}

int	error_exit(char *str, t_cub *cub)
{
	printf("Error\n");
	if (str)
		printf("%s\n", str);
	quit_cube(cub);
	return (-1);
}

int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr_until_idx(char **arr, int idx)
{
	int	i;

	i = -1;
	while (arr[++i] && i < idx)
		free(arr[i]);
}

void	find_player_init_pos(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (is_player_direction(cub->map[i][j]))
			{
				cub->player.pos.x = j + 0.5;
				cub->player.pos.y = i + 0.5;
				cub->player.initial_dir = cub->map[i][j];
				return ;
			}
		}
	}
}
