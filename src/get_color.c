/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:49:03 by sabakar-          #+#    #+#             */
/*   Updated: 2025/02/06 12:48:50 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	ft_check_end(char *sr)
{
	int	len;

	len = ft_strlen(sr) - 1;
	if (sr[len - 1] >= '0' && sr[len - 1] <= '9' && sr[0] >= '0'
		&& sr[0] <= '9')
		return (true);
	else
		return (false);
}

void	ft_set_color(t_cub *cub, char id, t_color color)
{
	if (id == 'C')
	{
		cub->c_color = color;
	}
	else if (id == 'F')
	{
		cub->f_color = color;
	}
}

int	ft_parse_color(char *color_str, t_color *color)
{
	char	**rgb;

	rgb = ft_split(color_str, ',');
	if (!rgb)
		return (-1);
	if (size_tab(rgb) != 3)
		return (tab_free(rgb), -2);
	color->r = pos_atoi(rgb[0]);
	color->g = pos_atoi(rgb[1]);
	color->b = pos_atoi(rgb[2]);
	tab_free(rgb);
	if ((color->r < 0 || color->r > 255) || (color->g < 0 || color->g > 255)
		|| (color->b < 0 || color->b > 255))
		return (-2);
	return (0);
}

void	ft_get_color(char **tab, t_cub *cub, char id)
{
	char	*color_str;
	int		err;
	t_color	color;

	if (!tab || size_tab(tab) != 2 || ft_strlen(tab[1]) == 1
		|| !ft_check_end(tab[1]))
		(tab_free(tab), error_exit("Format error. Example: C 225,30,0", cub));
	color_str = ft_strtrim(tab[1], "\n");
	if (!color_str)
		(tab_free(tab), error_exit(MEM_ERROR, cub));
	err = ft_parse_color(color_str, &color);
	if (err == -1)
		(free(color_str), tab_free(tab), error_exit(MEM_ERROR, cub));
	else if (err == -2)
		(free(color_str), tab_free(tab),
			error_exit("Format error. Example: C 225,30,0", cub));
	ft_set_color(cub, id, color);
	if (color_str)
		free(color_str);
	tab_free(tab);
}

bool	ft_check_after_six(t_lst **file_content)
{
	t_lst	*curr;
	int		x;

	curr = *file_content;
	x = 0;
	while (curr)
	{
		if (is_empty(curr->content))
		{
			curr = curr->next;
		}
		else if (!is_empty(curr->content))
		{
			while (((char *)curr->content)[x]
				&& ((char *)curr->content)[x] != '\n')
			{
				if (is_allowed_char(((char *)curr->content)[x]))
					x++;
				else
					return (false);
			}
			return (true);
		}
	}
	return (false);
}
