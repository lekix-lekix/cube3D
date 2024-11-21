/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:22:17 by inbennou          #+#    #+#             */
/*   Updated: 2024/11/21 14:37:52 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_texture(char **split_elem, t_list *file_content, t_list *start,
		t_cub *cub)
{
	split_elem = ft_split(file_content->content, ' ');
	if (split_elem && ft_strncmp(split_elem[0], "NO", 3) == 0)
		add_north(split_elem, start, cub);
	if (split_elem && ft_strncmp(split_elem[0], "SO", 3) == 0)
		add_south(split_elem, start, cub);
	if (split_elem && ft_strncmp(split_elem[0], "EA", 3) == 0)
		add_east(split_elem, start, cub);
	if (split_elem && ft_strncmp(split_elem[0], "WE", 3) == 0)
		add_west(split_elem, start, cub);
	if (split_elem && ft_strncmp(split_elem[0], "C", 2) == 0)
		get_color(split_elem, start, cub, 'C');
	if (split_elem && ft_strncmp(split_elem[0], "F", 2) == 0)
		get_color(split_elem, start, cub, 'F');
    cub->c_color.t = 0;
	free_tab(split_elem);
}

int	add_north(char **tab, t_list *start, t_cub *cub)
{
	if (size_tab(tab) != 2)
		texture_error(tab, start, cub,
			"Format error in elements: ID ./path_to_texture.");
	if (cub->no_text == NULL)
	{
		cub->no_text = ft_strdup(tab[1]);
		if (!cub->no_text)
			texture_error(tab, start, cub, "malloc error: add_north");
	}
	else
		texture_error(tab, start, cub,
			"Each ID can only have one texture path.");
	return (0);
}

int	add_south(char **tab, t_list *start, t_cub *cub)
{
	if (size_tab(tab) != 2)
		texture_error(tab, start, cub,
			"Format error in elements: ID ./path_to_texture.");
	if (cub->so_text == NULL)
	{
		cub->so_text = ft_strdup(tab[1]);
		if (!cub->so_text)
			texture_error(tab, start, cub, "malloc error: add_south");
	}
	else
		texture_error(tab, start, cub,
			"Each ID can only have one texture path.");
	return (0);
}

int	add_east(char **tab, t_list *start, t_cub *cub)
{
	if (size_tab(tab) != 2)
		texture_error(tab, start, cub,
			"Format error in elements: ID ./path_to_texture.");
	if (cub->ea_text == NULL)
	{
		cub->ea_text = ft_strdup(tab[1]);
		if (!cub->ea_text)
			texture_error(tab, start, cub, "malloc error: add_east");
	}
	else
		texture_error(tab, start, cub,
			"Each ID can only have one texture path.");
	return (0);
}

int	add_west(char **tab, t_list *start, t_cub *cub)
{
	if (size_tab(tab) != 2)
		texture_error(tab, start, cub,
			"Format error in elements: ID ./path_to_texture.");
	if (cub->we_text == NULL)
	{
		cub->we_text = ft_strdup(tab[1]);
		if (!cub->we_text)
			texture_error(tab, start, cub, "malloc error: add_west");
	}
	else
		texture_error(tab, start, cub,
			"Each ID can only have one texture path.");
	return (0);
}
