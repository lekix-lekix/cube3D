/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_characters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:19:03 by kipouliq          #+#    #+#             */
/*   Updated: 2025/01/17 11:22:28 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_is_space(char c)
{
	return (c == ' ');
}

int	is_allowed_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '1' || c == '0'
		|| c == ' ' || c == 'D');
}

int	is_player_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_map_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '1'
		|| c == '0');
}

int	check_sides_space(char **map, int i, int j)
{
	return (ft_is_space(map[i - 1][j]) || ft_is_space(map[i + 1][j])
		|| ft_is_space(map[i][j - 1]) || ft_is_space(map[i][j + 1]));
}
