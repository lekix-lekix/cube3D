/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_checking.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:20:55 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/16 12:56:26 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_lst	*ft_get_file_content(int fd);
int		get_elems(t_lst *file_content, t_cub *cub);

// void	ft_print_lst(t_lst *lst)
// {
//     if (!lst) {
//         printf("List is empty.\n");
//         return ;
//     }

//     printf("Printing list:\n");
//     while (lst)
//     {
//         if (lst->content)
//             printf("%s\n", (char *)lst->content);
//         else
//             printf("Node content is NULL.\n");
//         lst = lst->next;
//     }
// }

int	ft_check_extension(char *sr)
{
	int	len;

	len = ft_strlen(sr);
	while (sr[--len] && sr[len] != '.')
		if (sr[len] != 'c' && sr[len] != 'u' && sr[len] != 'b')
			return (printf("Err.\nInvalid file extension\n"), 0);
	return (1);
}

int	ft_read_file(char *file_path, t_cub *cub)
{
	int		fd;
	t_lst	*file_content;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (printf("Can't open file.\n"), 0);
	file_content = ft_get_file_content(fd);
	if (!file_content || ft_lstsize(file_content) < 8)
	{
		if (file_content)
			free_list(file_content);
		return (printf("Your file is missing elements.\n"), 0);
	}
	if (!get_elems(file_content, cub))
		return (free_list(file_content), 0);
	skip_elements(&file_content);
	cub->map = get_map(cub, &file_content);
	free_list(file_content);
	return (1);
}

t_lst	*ft_get_file_content(int fd)
{
	char	*line;
	t_lst	*lines;
	t_lst	*head;
	t_lst	*tmp;

	head = NULL;
	while ((line = get_next_line(fd, 0)) != NULL && line[0] != '\0')
	{
		tmp = ft_lstnew(line);
		if (!tmp)
			return (free_list(head), free_line(line), NULL);
		if (!head)
			head = tmp;
		else
			ft_lstadd_back(&lines, tmp);
		lines = tmp;
	}
	// if (line)
		// (free(line), get_next_line(0, 0));
	// get_next_line(0, 0);
	// if (tmp)
	// {
	// 	printf("Yeah, fuck it\n");
	// 	free_list(tmp);
	// }
	if (fd > 0)
		close(fd);
	return (head);
}

int	get_elems(t_lst *file_content, t_cub *cub)
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
				add_texture(split_elem, file_content, cub);
			else
				return (ft_free_and_return(split_elem, cub), 0);
			x++;
			file_content = file_content->next;
		}
	}
	return (1);
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
