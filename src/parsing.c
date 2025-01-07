/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:13:50 by inbennou          #+#    #+#             */
/*   Updated: 2024/12/15 21:21:18 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parsing(int ac, char **av, t_list **start, t_cub *cub)
{
	int		fd;
	t_list	*file_content;
	t_list	*current;

	if (ac != 2)
		return (map_error(-1, "This program takes one argument (the map).",
				NULL), 1);
	if (name_check(av[1]))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (map_error(-1, "Can't open file.", NULL), 1);
	file_content = get_file(fd);
	*start = file_content;
	if (!file_content || ft_lstsize(file_content) < 8)
		return (map_error(fd,
				"You should have 6 elements and 1 map in your file.",
				file_content), 1);
	if (fd > 0)
		close(fd);
	if (!get_elems(file_content, cub, *start))
		return (1);
	skip_elements(&file_content);
	cub->map = get_map(cub, &file_content);
	return (current = file_content, check_map(cub), free_list(*start), 0);
}

int	name_check(char *str)
{
	int	i;

	if (!str || !str[0])
		return (map_error(-1, "Invalid name. The map must have .cub extension.",
				NULL), 1);
	i = ft_strlen(str) - 1;
	if (str[i] != 'b' || str[i - 1] != 'u' || str[i - 2] != 'c' || str[i
			- 3] != '.')
		return (map_error(-1, "Invalid name. The map must have .cub extension.",
				NULL), 1);
	return (0);
}

t_list	*get_file(int fd)
{
	char	*line;
	t_list	*list;
	t_list	*start;
	t_list	*tmp;

	line = get_next_line(fd, 0);
	if (!line || line[0] == '\0')
		return (NULL);
	list = ft_lstnew(line);
	if (!list)
		return (free_line(line), NULL);
	start = list;
	while (ft_find(line, '\n'))
	{
		line = get_next_line(fd, 0);
		if (!line || line[0] == '\0')
			return (free_list(start), free_line(line), NULL);
		tmp = ft_lstnew(line);
		if (!tmp)
			return (free_list(start), free_line(line), NULL);
		ft_lstadd_back(&list, tmp);
		list = list->next;
	}
	return (start);
}

void	ft_another_function(t_cub *cub)
{
	if (cub->ea_text)
	{
		if (cub->ea_text->text_img && cub->ea_text->text_img->img_ptr)
			mlx_destroy_image(cub->mlx_data.mlx_ptr,
				cub->ea_text->text_img->img_ptr);
		(free(cub->ea_text->text_img), free(cub->ea_text));
	}
	if (cub->we_text)
	{
		if (cub->we_text->text_img && cub->we_text->text_img->img_ptr)
			mlx_destroy_image(cub->mlx_data.mlx_ptr,
				cub->we_text->text_img->img_ptr);
		(free(cub->we_text->text_img), free(cub->we_text));
	}
}

void	ft_free_and_return(char **split_elem, t_list *start, t_cub *cub)
{
	if (split_elem)
		free_tab(split_elem);
	(void)start;
	if (start)
		free_list(start);
	dprintf(2, "Error\n");
	dprintf(2, "Can't open the file or one of the elems is not right.\n");
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
