/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:43:10 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/23 13:48:55 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	free_list(t_lst *list)
{
	t_lst	*tmp;

	while (list)
	{
		tmp = list;
		free(tmp->content);
		free(tmp);
		list = list->next;
	}
	return (0);
}

void	ft_free(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

int	size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	handle_destroy(t_cub *cub)
{
	quit_cube(cub);
	exit(0);
}

void	ft_free_and_return(char **split_elem, t_cub *cub)
{
	if (split_elem)
		tab_free(split_elem);
	printf("Error\n");
	printf("Can't open the file or one of the elems is NOT right.\n");
	ft_another_function(cub);
	if (cub->no_text)
	{
		if (cub->no_text->text_img && cub->no_text->text_img->img_ptr)
			mlx_destroy_image(cub->mlx_data.mlx_ptr,
				cub->no_text->text_img->img_ptr);
		(free(cub->no_text->text_img), free(cub->no_text));
	}
	if (cub->so_text)
	{
		if (cub->so_text->text_img && cub->so_text->text_img->img_ptr)
			mlx_destroy_image(cub->mlx_data.mlx_ptr,
				cub->so_text->text_img->img_ptr);
		(free(cub->so_text->text_img), free(cub->so_text));
	}
}
