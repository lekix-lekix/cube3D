/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:30:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/12/12 15:30:42 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	exit_map_not_valid(t_cub *cub, int err)
{
	printf("Error\n");
	if (err == 1)
		printf("Open map detected.\n");
	if (err == 2)
		printf("Forbidden character detected.\n");
	if (err == 3)
		printf("Multiple players detected.\n");
	if (err == 4)
		printf("No player detected.\n");
	free_cub(cub);
	exit(EXIT_FAILURE);
}

void	map_error(int fd, char *msg, t_list *file_content)
{
	printf("Error\n%s\n", msg);
	if (fd > 0)
		close(fd);
	if (file_content)
		free_list(file_content);
}

void	texture_error(char **tab, t_list *start, t_cub *cub, char *msg)
{
	if (tab)
		free_tab(tab);
	free_cub(cub);
	map_error(-1, msg, start);
}

void	color_error(char **tab, t_list *start, t_cub *cub, char *color)
{
	ft_free(color);
	texture_error(tab, start, cub, "Format error. exemple: C 225,30,0");
}
