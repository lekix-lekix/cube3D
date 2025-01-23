/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:23:07 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/16 17:07:23 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_line(char *line)
{
	ft_free(line);
	get_next_line(0, 1);
}

void	free_cub(t_cub *cub)
{
	free(cub->ea_text);
	free(cub->so_text);
	free(cub->no_text);
	free(cub->we_text);
	if (cub->map)
		tab_free(cub->map);
}

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\r' || c == '\f' || c == '\t' || c == '\v'))
		return (true);
	return (false);
}

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]) || str[i] == '\n')
		i++;
	if (i == (int)ft_strlen(str)) // If the line aka the str is empty, we return true.
		return (true);
	return (false);
}

char	*ft_remove_newline(char *sr)
{
    int	p;
    int	q;
    char *res;

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
	int	fd;
	char	**fpath;
	char	*path_wnl;

	fpath = ft_split(sr, 32);
	path_wnl = ft_remove_newline(fpath[1]);
	fd = open(path_wnl, O_RDWR);
	free(path_wnl);
	tab_free(fpath);
	if (fd >= 0)
		return (close(fd), 1);
	else
		return (0);
}

int	is_elem(char *str)
{
	if (!str)
		return (false);
	if ((ft_strncmp(str, "NO", 2) == 0) && (check_file(str)))
		return (true);
	if ((ft_strncmp(str, "SO", 2) == 0) && (check_file(str)))
		return (true);
	if ((ft_strncmp(str, "EA", 2) == 0) && (check_file(str)))
		return (true);
	if ((ft_strncmp(str, "WE", 2) == 0) && (check_file(str)))
		return (true);
	if (str[0] == 'F')
		return (true);
	if (str[0] == 'C')
		return (true);
	else
		return (false);
}
