/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:20:05 by kipouliq          #+#    #+#             */
/*   Updated: 2025/02/06 12:30:40 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_lstsize_check_empty(t_lst **lst)
{
	t_lst	*current;
	int		i;

	i = 0;
	current = *lst;
	while (current)
	{
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
		return (error_exit(MEM_ERROR, cub), NULL);
	i = 0;
	current = *file;
	while (current)
	{
		map[i] = ft_remove_newline(current->content);
		if (!map[i])
			return (free_arr_until_idx(map, i), free(map), error_exit(MEM_ERROR,
					cub), NULL);
		i++;
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
				return (err_map_not_valid(1), -1);
			if (!is_allowed_char(cub->map[i][j]))
				return (err_map_not_valid(2), -1);
			if (player_found && is_player_direction(cub->map[i][j]))
				return (err_map_not_valid(3), -1);
			else if (is_player_direction(cub->map[i][j]))
				player_found = 1;
		}
	}
	if (!player_found)
		return (err_map_not_valid(4), -1);
	return (0);
}
