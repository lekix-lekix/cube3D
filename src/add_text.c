/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:22:17 by inbennou          #+#    #+#             */
/*   Updated: 2024/12/12 15:30:30 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_texture(char **split_elem, t_list *file_content, t_list *start,
		t_cub *cub)
{
	split_elem = ft_split(file_content->content, ' ');
	if (split_elem && ft_strncmp(split_elem[0], "NO", 3) == 0)
		init_texture(split_elem, start, cub, &cub->no_text);
	if (split_elem && ft_strncmp(split_elem[0], "SO", 3) == 0)
		init_texture(split_elem, start, cub, &cub->so_text);
	if (split_elem && ft_strncmp(split_elem[0], "EA", 3) == 0)
		init_texture(split_elem, start, cub, &cub->ea_text);
	if (split_elem && ft_strncmp(split_elem[0], "WE", 3) == 0)
		init_texture(split_elem, start, cub, &cub->we_text);
	if (split_elem && ft_strncmp(split_elem[0], "C", 2) == 0)
		get_color(split_elem, start, cub, 'C');
	if (split_elem && ft_strncmp(split_elem[0], "F", 2) == 0)
		get_color(split_elem, start, cub, 'F');
	cub->c_color.t = 0;
	free_tab(split_elem);
}

int	init_texture(char **tab, t_list *start, t_cub *cub, t_texture **cub_text)
{
	char	*path;

	if (size_tab(tab) != 2)
		texture_error(tab, start, cub,
			"Format error in elements: ID ./path_to_texture.");
	if (*cub_text == NULL)
	{
		path = ft_strtrim(tab[1], "\n");
		if (!path)
			return (error_exit(MEM_ERROR, cub), -1);
		*cub_text = init_mlx_img_texture(cub, path);
		free(path);
	}
	else
		texture_error(tab, start, cub,
			"Each ID can only have one texture path.");
	return (0);
}

int	get_elems(t_list *file_content, t_cub *cub, t_list *start)
{
	char	**split_elem;
	int		x;

	x = 0;
	split_elem = NULL;
	while (file_content && x < 6)
	{
		if (is_empty(file_content->content))
			file_content = file_content->next;
		else
		{
			if (is_elem(file_content->content))
				add_texture(split_elem, file_content, start, cub);
			else
				return (ft_free_and_return(split_elem, start, cub), 0);
			x++;
			file_content = file_content->next;
		}
	}
	return (1);
}