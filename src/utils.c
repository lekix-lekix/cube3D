/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:23:07 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/28 18:50:33 by kipouliq         ###   ########.fr       */
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

int	check_file(char *sr)
{
	int		fd;
	char	**fpath;
	char	*path_wnl;

	fpath = ft_split(sr, 32);
	if (!fpath)
		return (0);
	if (size_tab(fpath) != 2)
		return (tab_free(fpath), 0);
	path_wnl = ft_remove_newline(fpath[1]);
	if (!path_wnl)
		return (tab_free(fpath), 0);
	fd = open(path_wnl, O_RDWR);
	free(path_wnl);
	tab_free(fpath);
	if (fd >= 0)
		return (close(fd), 1);
	else
		return (0);
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
