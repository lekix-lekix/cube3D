/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:03:53 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/30 18:33:39 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	add_texture(char **split_elem, t_lst *current, t_lst **file_content,
		t_cub *cub)
{
	split_elem = ft_split(current->content, ' ');
	if (!split_elem)
	{
		ft_lstclear(file_content, free);
		error_exit(MEM_ERROR, cub);
		return ;
	}
	if (ft_strncmp(split_elem[0], "NO", 2) == 0)
		ft_check_textures(split_elem, cub, &cub->no_text);
	else if (ft_strncmp(split_elem[0], "SO", 2) == 0)
		ft_check_textures(split_elem, cub, &cub->so_text);
	else if (ft_strncmp(split_elem[0], "EA", 2) == 0)
		ft_check_textures(split_elem, cub, &cub->ea_text);
	else if (ft_strncmp(split_elem[0], "WE", 2) == 0)
		ft_check_textures(split_elem, cub, &cub->we_text);
	else if (ft_strncmp(split_elem[0], "C", 1) == 0)
		ft_get_color(split_elem, cub, 'C');
	else if (ft_strncmp(split_elem[0], "F", 1) == 0)
		ft_get_color(split_elem, cub, 'F');
	cub->c_color.t = 0;
}

t_texture	*alloc_mlx_texture(t_cub *cub, char *path)
{
	t_texture	*text;

	text = malloc(sizeof(t_texture));
	if (!text)
		return (free(path), error_exit(MEM_ERROR, cub), NULL);
	text->path = path;
	text->text_img = NULL;
	return (text);
}

int	ft_check_textures(char **tab, t_cub *cub, t_texture **cub_text)
{
	char	*path;

	if (*cub_text)
		return (tab_free(tab), error_exit("Double detected", cub), 0);
	if (size_tab(tab) != 2)
	{
		printf("Error\nFormat error in elements: ID ./path_to_texture.\n");
		return (tab_free(tab), quit_cube(cub));
	}
	path = ft_strtrim(tab[1], "\n");
	tab_free(tab);
	if (!path)
		return (error_exit(MEM_ERROR, cub), 0);
	*cub_text = alloc_mlx_texture(cub, path);
	return (1);
}
