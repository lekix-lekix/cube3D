/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:20:05 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/21 17:07:04 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_lstsize_check_empty(t_list **lst)
{
	t_list	*current;
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

char	**get_map(t_list **file)
{
	char	**map;
	int		i;
	t_list	*current;

	map = malloc(sizeof(char *) * (ft_lstsize_check_empty(file) + 1));
	if (!map)
		return (error_exit(NULL), NULL);
	i = 0;
	current = *file;
	while (current)
	{
		if (!is_empty(current->content))
		{
			map[i] = ft_strtrim(current->content, "\n");
			if (!map[i])
				return (free_arr_until_idx(map, i), error_exit(NULL), NULL);
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

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	char	**map;
// 	t_lst	*node;
// 	t_lst	*lst;
// 	int		i;

// 	(void)argc;
// 	(void)argv;
// 	lst = NULL;
// 	fd = open("./map.cub", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd, 0);
// 		if (!line)
// 			break ;
// 		node = ft_lstnew((void *)line);
// 		ft_lstadd_back(&lst, node);
// 	}
// 	map = get_map(&lst);
// 	i = -1;
// 	while (map[++i])
// 		printf("%s\n", map[i]);
// 	if (check_map(map) == 0)
// 		printf("valid map content\n");
// 	else
// 		printf("not valid map\n");
// 	if (start_mlx(800, 800, map) == -1)
// 		return (-1);
// }
