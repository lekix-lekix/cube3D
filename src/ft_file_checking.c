/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_checking.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:20:55 by sabakar-          #+#    #+#             */
/*   Updated: 2025/02/04 15:12:57 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_lst(t_lst **file_content)
{
	t_lst	*current;

	current = *file_content;
	if (!current)
		printf("sljjdf\n");
	while (current)
	{
		printf("%s", (char *)current->content);
		current = current->next;
	}
}

int	ft_check_extension(char *sr)
{
	int	len;
	int	x;

	x = 0;
	len = ft_strlen(sr);
	while (sr[--len] && sr[len] != '.' && x < 3)
	{
		if (sr[len] != 'c' && sr[len] != 'u' && sr[len] != 'b')
			return (printf("Err.\nInvalid file extension\n"), 0);
		x++;
	}
	if (x != 3 || sr[len] != '.')
		return (printf("Err.\nInvalid file extension\n"), 0);
	return (1);
}

void	ft_get_file_content(int fd, t_lst **file_content)
{
	char	*line;
	t_lst	*new_node;
	int		i;

	i = 0;
	line = get_next_line(fd, 0);
	while (line && line[0] != '\0')
	{
		new_node = ft_lstnew(line);
		if (!new_node)
		{
			ft_lstclear(file_content, free);
			free(line);
			get_next_line(fd, 1);
			close(fd);
			return ;
		}
		ft_lstadd_back(file_content, new_node);
		line = get_next_line(fd, 0);
		i++;
	}
	get_next_line(0, 1);
	close(fd);
}

int	get_elems(t_lst **file_content, t_cub *cub)
{
	char	**split_elem;
	t_lst	*current;
	int		x;

	x = 0;
	split_elem = NULL;
	current = *file_content;
	while (current && x < 6)
	{
		if (is_empty(current->content) == 1)
			current = current->next;
		else
		{
			if (is_elem(current->content, cub))
				add_texture(split_elem, current, file_content, cub);
			else
				return (printf("Error\n"), printf("%s\n", ELEM_ERR), 0);
			x++;
			current = current->next;
		}
	}
	current = current->next;
	if (!ft_check_after_six(&current))
		return (printf("Error\n"), printf("%s\n", ELEM_ERR), 0);
	return (1);
}

int	ft_read_file(char *file_path, t_cub *cub)
{
	int		fd;
	t_lst	*file_content;
	t_lst	*clean_content;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (printf("Error\n"), printf("Can't open file.\n"), 0);
	file_content = NULL;
	ft_get_file_content(fd, &file_content);
	if (!file_content || ft_lstsize(file_content) < 8)
	{
		if (file_content)
			ft_lstclear(&file_content, free);
		return (printf("Error\n"), printf("Your file is missing elements.\n"),
			0);
	}
	cub->file_content = &file_content;
	if (!get_elems(&file_content, cub))
		return (ft_lstclear(&file_content, free), quit_cube(cub), -1);
	clean_content = skip_elements(&file_content);
	cub->map = get_map(cub, &clean_content);
	ft_lstclear(cub->file_content, free);
	cub->file_content = NULL;
	return (1);
}
