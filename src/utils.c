/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:29:44 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/15 17:07:04 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_line(char *line)
{
	ft_free(line);
	get_next_line(0, 1);
}

void	free_cub(t_cub *cub)
{
	ft_free(cub->ea_text);
	ft_free(cub->so_text);
	ft_free(cub->no_text);
	ft_free(cub->we_text);
	if (cub->map)
		free_tab(cub->map);
}

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\r' || c == '\f' || c == '\t' || c == '\v'))
		return (true);
	return (false);
}

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]) || str[i] == '\n')
		i++;
	if (i == ft_strlen(str))
		return (true);
	return (false);
}

bool	is_elem(char *str)
{
	if (!str)
		return (false);
	if (ft_strncmp(str, "NO", 2) == 0)
		return (true);
	if (ft_strncmp(str, "SO", 2) == 0)
		return (true);
	if (ft_strncmp(str, "EA", 2) == 0)
		return (true);
	if (ft_strncmp(str, "WE", 2) == 0)
		return (true);
	if (str[0] == 'F')
		return (true);
	if (str[0] == 'C')
		return (true);
	else
		return (false);
}
