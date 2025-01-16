/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_checking.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:20:55 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/16 18:10:37 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_get_file_content(int fd, t_lst **file_content);
int get_elems(t_lst *file_content, t_cub *cub);

void ft_print_lst(t_lst *lst)
{
	if (!lst)
	{
		printf("List is empty.\n");
		return;
	}
	printf("Printing list:\n");
	while (lst)
	{
		if (lst->content)
			printf("%s", (char *)lst->content);
		else
			printf("Node content is NULL.\n");
		lst = lst->next;
	}
}

int ft_check_extension(char *sr)
{
	int len;

	len = ft_strlen(sr);
	while (sr[--len] && sr[len] != '.')
		if (sr[len] != 'c' && sr[len] != 'u' && sr[len] != 'b')
			return (printf("Err.\nInvalid file extension\n"), 0);
	return (1);
}

int ft_read_file(char *file_path, t_cub *cub)
{
	int fd;
	t_lst *file_content;
	t_lst *clean_content;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (printf("Can't open file.\n"), 0);
	// file_content = ft_get_file_content(fd);
	file_content = NULL;
	ft_get_file_content(fd, &file_content);
	if (!file_content || ft_lstsize(file_content) < 8)
	{
		if (file_content)
			ft_lstclear(&file_content, free);
		return (printf("Your file is missing elements.\n"), 0);
	}
	if (!get_elems(file_content, cub))
	{
		printf("ca sort la ?\n");
		ft_lstclear(&file_content, free);
		return (quit_cube(cub), -1);
	}
	clean_content = skip_elements(&file_content);
	// printf("file content first = %s\n", file_content->content)
	ft_print_lst(clean_content);
	cub->map = get_map(cub, &clean_content);
	printf("here\n");
	ft_lstclear(&clean_content, free);
	get_next_line(0, 1);
	// free(line);
	// free_list(file_content);
	// free(file_content);
	// ft_print_lst(file_content);
	return (1);
}

void ft_get_file_content(int fd, t_lst **file_content)
{
	char *line;
	t_lst *new_node;
	int i = 0;
	// t_lst	*lines;
	// t_lst	*head;
	// t_lst	*tmp;

	// head = NULL;
	while ((line = get_next_line(fd, 0)) != NULL && line[0] != '\0')
	{
		new_node = ft_lstnew(line);
		if (!new_node)
		{
			printf("no new node\n");
			return; // to protect
		}
		// return (free_list(*file_content), free_line(line), NULL);
		// if (!head)
		// 	head = tmp;
		ft_lstadd_back(file_content, new_node);
		i++;
		// free(line);
		// lines = tmp;
	}
	if (line)
	{
		printf("yes line\n");
		(free(line), get_next_line(0, 0));
	}
	// get_next_line(0, 0);
	// if (tmp)
	// {
	// 	printf("Yeah, fuck it\n");
	// 	free_list(tmp);
	// }
	if (fd > 0)
		close(fd);
	printf("%d elements created\n", i);
	// return (head);
}

// t_lst	*ft_get_file_content(int fd, t_lst **file_content)
// {
// 	char	*line;
// 	t_lst	*lines;
// 	t_lst	*head;
// 	t_lst	*tmp;

// 	head = NULL;
// 	while ((line = get_next_line(fd, 0)) != NULL && line[0] != '\0')
// 	{
// 		tmp = ft_lstnew(line);
// 		if (!tmp)
// 			return (free_list(head), free_line(line), NULL);
// 		if (!head)
// 			head = tmp;
// 		else
// 			ft_lstadd_back(&lines, tmp);
// 		lines = tmp;
// 	}
// 	// if (line)
// 		// (free(line), get_next_line(0, 0));
// 	// get_next_line(0, 0);
// 	// if (tmp)
// 	// {
// 	// 	printf("Yeah, fuck it\n");
// 	// 	free_list(tmp);
// 	// }
// 	if (fd > 0)
// 		close(fd);
// 	// get_next_line(0, 1);
// 	return (head);
// }

int get_elems(t_lst *file_content, t_cub *cub)
{
	char **split_elem;
	int x;

	x = 0;
	split_elem = NULL;
	while (file_content && x < 6)
	{
		if (is_empty(file_content->content))
			file_content = file_content->next;
		else
		{
			if (is_elem(file_content->content))
				add_texture(split_elem, file_content, cub);
			else
			{
				printf("Error\n");
				printf("Can't open the file or one of the elems is NOT right.\n");
				return (0);
			}
			x++;
			file_content = file_content->next;
		}
	}
	return (1);
}

void ft_another_function(t_cub *cub)
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
