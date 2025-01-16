/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:03:53 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/16 11:53:28 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_texture(char **split_elem, t_lst *file_content, t_cub *cub)
{
    split_elem = ft_split(file_content->content, ' ');
    if (!split_elem)
        return;
    if (ft_strncmp(split_elem[0], "NO", 3) == 0)
        ft_check_textures(split_elem, cub, &cub->no_text);
    else if (ft_strncmp(split_elem[0], "SO", 3) == 0)
        ft_check_textures(split_elem, cub, &cub->so_text);
    else if (ft_strncmp(split_elem[0], "EA", 3) == 0)
        ft_check_textures(split_elem, cub, &cub->ea_text);
    else if (ft_strncmp(split_elem[0], "WE", 3) == 0)
        ft_check_textures(split_elem, cub, &cub->we_text);
    else if (ft_strncmp(split_elem[0], "C", 2) == 0)
        ft_get_color(split_elem, cub, 'C');
    else if (ft_strncmp(split_elem[0], "F", 2) == 0)
        ft_get_color(split_elem, cub, 'F');
    cub->c_color.t = 0;
    tab_free(split_elem);
}

int ft_check_textures (char **tab, t_cub *cub, t_texture **cub_text)
{
 	if (size_tab(tab) != 2)
        return (texture_error(tab, cub, "Format error in elements: ID ./path_to_texture."), 0);
    char *path = ft_strtrim(tab[1], "\n");
    if (!path)
        return (error_exit(MEM_ERROR, cub), 0);
    *cub_text = init_mlx_img_texture(cub, path);
    free(path);
    return 1;
}

    // if (*cub_text != NULL)
        // return (texture_error(tab, cub, "Each ID can only have one texture path."), 0);