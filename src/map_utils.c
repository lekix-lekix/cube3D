/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:04:59 by kipouliq          #+#    #+#             */
/*   Updated: 2025/01/23 13:57:40 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_lst	*skip_elements(t_lst **file_content)
{
	int		i;
	t_lst	*current;
	t_lst	*tmp;

	current = *file_content;
	i = 0;
	while (current && i < 6)
	{
		if (!is_empty(current->content))
			i++;
		tmp = current->next;
		free(current->content);
		free(current);
		current = tmp;
	}
	return (current);
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
