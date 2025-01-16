/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:03:15 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/16 16:52:21 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	err_map_not_valid(int err)
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
}

void	map_error(int fd, char *msg, t_lst *file_content)
{
	printf("Error\n%s\n", msg);
	if (fd > 0)
		close(fd);
	if (file_content)
		free_list(file_content);
}

void	texture_error(char **tab, t_cub *cub, char *msg)
{
	if (tab)
		tab_free(tab);
	free_cub(cub);
	map_error(-1, msg, NULL);
}

void	color_error(char **tab, t_cub *cub, char *color)
{
	ft_free(color);
	texture_error(tab, cub, "Format error. exemple: C 225,30,0");
}
