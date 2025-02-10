/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuz_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:19 by sabakar-          #+#    #+#             */
/*   Updated: 2025/02/10 13:55:13 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <string.h>

int	check_file(char **fpath)
{
	int		fd;
	char	*path_wnl;

	if (size_tab(fpath) != 2)
		return (0);
	path_wnl = ft_remove_newline(fpath[1]);
	if (!path_wnl)
		return (0);
	fd = open(path_wnl, O_RDWR);
	free(path_wnl);
	if (fd >= 0)
		return (close(fd), 1);
	else
		return (0);
}

int	is_elem(char *str, t_cub *cub)
{
	char	**fpath;

	if (!str)
		return (false);
	fpath = ft_split(str, ' ');
	if (!fpath)
		return (error_exit(MEM_ERROR, cub));
	if (size_tab(fpath) > 2)
		return (tab_free(fpath), false);
	if (!check_color_textures_name(fpath))
		return (tab_free(fpath), false);
	if (ft_strlen(fpath[0]) > 1 && !check_file(fpath))
		return (tab_free(fpath), false);
	return (tab_free(fpath), true);
}

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]) || str[i] == '\n')
		i++;
	if (i == (int)ft_strlen(str))
		return (true);
	return (false);
}
