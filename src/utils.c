/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:23:07 by sabakar-          #+#    #+#             */
/*   Updated: 2025/02/04 15:01:53 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\r' || c == '\f' || c == '\t' || c == '\v'))
		return (true);
	return (false);
}

char	*ft_remove_newline(char *sr)
{
	int		p;
	int		q;
	char	*res;

	p = 0;
	q = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(sr) + 1));
	if (!res)
		return (NULL);
	while (sr[p])
	{
		if (sr[p] != '\n')
			res[q++] = sr[p];
		p++;
	}
	res[q] = '\0';
	return (res);
}

bool check_color_textures_name(char **fpath)
{
	if (ft_strncmp(fpath[0], "NO", ft_strlen(fpath[0])) != 0 &&
	ft_strncmp(fpath[0], "SO", ft_strlen(fpath[0])) != 0 &&
	ft_strncmp(fpath[0], "EA", ft_strlen(fpath[0])) != 0 &&
	ft_strncmp(fpath[0], "WE", ft_strlen(fpath[0])) != 0 &&
	ft_strncmp(fpath[0], "F", ft_strlen(fpath[0])) != 0 &&
	ft_strncmp(fpath[0], "C", ft_strlen(fpath[0])) != 0)
		return (false);
	return (true);
}

int	size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

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
