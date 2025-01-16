/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:20:05 by kipouliq          #+#    #+#             */
/*   Updated: 2025/01/16 13:14:49 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
void	ft_another_destroy_cub(t_cub *cub);

int	ft_lstsize_check_empty(t_lst **lst)
{
	t_lst	*current;
	int		i;

	i = 0;
	current = *lst;
	while (current)
	{
		if (!is_empty(current->content))
			i++;
		current = current->next;
	}
	return (i);
}

char	**get_map(t_cub *cub, t_lst **file)
{
	char	**map;
	int		i;
	t_lst	*current;

	map = malloc(sizeof(char *) * (ft_lstsize_check_empty(file) + 1));
	if (!map)
		return (error_exit(NULL, cub), NULL);
	i = 0;
	current = *file;
	while (current)
	{
		if (!is_empty(current->content))
		{
			map[i] = ft_strtrim(current->content, "\n");
			if (!map[i])
				return (free_arr_until_idx(map, i), error_exit(NULL, cub),
					NULL);
			i++;
		}
		current = current->next;
	}
	map[i] = NULL;
	return (map);
}

int	check_sides_null(char **map, int i, int j)
{
	if (!map[i][j - 1] || !map[i][j + 1])
		return (1);
	if (j > (int)ft_strlen(map[i - 1]) - 1 || j > (int)ft_strlen(map[i + 1])
		- 1)
		return (1);
	return (0);
}

int	is_border(char **map, int i, int j)
{
	if (is_map_char(map[i][j]))
	{
		if (i == 0 || j == 0 || j == (int)ft_strlen(map[i]) - 1
			|| i == get_arr_size(map) - 1)
			return (1);
		if (check_sides_null(map, i, j) || check_sides_space(map, i, j))
			return (1);
	}
	return (0);
}

int	check_map(t_cub *cub)
{
	int	i;
	int	j;
	int	player_found;

	i = -1;
	player_found = 0;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (is_border(cub->map, i, j) && cub->map[i][j] != '1')
				return (exit_map_not_valid(cub, 1), -1);
			if (!is_allowed_char(cub->map[i][j]))
				return (exit_map_not_valid(cub, 2), -1);
			if (player_found && is_player_direction(cub->map[i][j]))
				return (exit_map_not_valid(cub, 3), -1);
			else if (is_player_direction(cub->map[i][j]))
				player_found = 1;
		}
	}
	if (!player_found)
		return (exit_map_not_valid(cub, 4), -1);
	return (0);
}

// void	ft_another_destroy_cub(t_cub *cub)
// {
// 	mlx_destroy_window(cub->mlx_data.mlx_ptr, cub->mlx_data.win_ptr);
// 	mlx_destroy_display(cub->mlx_data.mlx_ptr);
// 	free(cub->mlx_data.mlx_ptr);
// }
