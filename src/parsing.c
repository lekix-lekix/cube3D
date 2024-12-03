/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:13:50 by inbennou          #+#    #+#             */
/*   Updated: 2024/12/03 14:48:46 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parsing(int ac, char **av, t_list **start, t_cub *cub)
{
	int		fd;
	t_list	*file_content;
	t_list	*current;

	if (ac != 2)
		map_error(-1, "This program takes one argument (the map).", NULL);
	name_check(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0) // perror ?
		map_error(-1, "Can't open file.", NULL);
	file_content = get_file(fd);
	*start = file_content;
	if (!file_content || ft_lstsize(file_content) < 8)
		map_error(fd, "You should have 6 elements and 1 map in your file.",
			file_content);
	if (fd > 0)
		close(fd);
	get_elems(file_content, cub, *start);
	skip_elements(&file_content);
	cub->map = get_map(cub, &file_content);
	current = file_content;
	check_map(cub);
	free_list(*start);
}

void	name_check(char *str)
{
	int	i;

	if (!str || !str[0])
		map_error(-1, "Invalid name. Must have .cub extension.", NULL);
	i = ft_strlen(str) - 1;
	if (str[i] != 'b' || str[i - 1] != 'u' || str[i - 2] != 'c' || str[i
		- 3] != '.')
		map_error(-1, "Invalid name. Must have .cub extension.", NULL);
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

void	elems_check(char **split_elem, t_list *start, t_cub *cub)
{
	if (!cub->ea_text)
		texture_error(split_elem, start, cub, "EA texture missing.");
	if (!cub->no_text)
		texture_error(split_elem, start, cub, "NO texture missing.");
	if (!cub->so_text)
		texture_error(split_elem, start, cub, "SO texture missing.");
	if (!cub->we_text)
		texture_error(split_elem, start, cub, "WE texture missing.");
	// if (cub->c_color < 0)
	// 	texture_error(split_elem, start, cub, "C color missing.");
	// if (cub->f_color < 0)
	// 	texture_error(split_elem, start, cub, "F color missing.");
}

bool	get_elems(t_list *file_content, t_cub *cub, t_list *start)
{
	int		i;
	char	**split_elem;

	i = 0;
	split_elem = NULL;
	while (file_content && i < 6)
	{
		if (is_empty(file_content->content))
			file_content = file_content->next;
		else
		{
			if (is_elem(file_content->content))
				add_texture(split_elem, file_content, start, cub);
			i++;
			file_content = file_content->next;
		}
	}
	elems_check(split_elem, start, cub);
	return (true);
}
