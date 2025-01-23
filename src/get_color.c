/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:49:03 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/23 14:13:41 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_parse_color(char *color_str, t_color *color, t_cub *cub);
void	ft_set_color(t_cub *cub, char id, t_color color);

void	ft_get_color(char **tab, t_cub *cub, char id)
{
	char	*color_str;
	t_color	color;

	if (!tab || size_tab(tab) != 2)
		return (texture_error(tab, cub, "Format error. Example: C 225,30,0"));
	color_str = ft_strtrim(tab[1], "\n");
	if (!color_str)
		return (color_error(tab, cub, NULL));
	if (ft_parse_color(color_str, &color, cub) == -1)
		return (ft_free(color_str));
	ft_set_color(cub, id, color);
	ft_free(color_str);
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

int	ft_parse_color(char *color_str, t_color *color, t_cub *cub)
{
	char	**rgb;

	rgb = ft_split(color_str, ',');
	if (!rgb)
		return (color_error(NULL, cub, color_str), -1);
	color->r = pos_atoi(rgb[0]);
	color->g = pos_atoi(rgb[1]);
	color->b = pos_atoi(rgb[2]);
	tab_free(rgb);
	if (color->r < 0 || color->g < 0 || color->b < 0)
		return (texture_error(NULL, cub,
				"Format error. It should contain something like: C 225,30,0"),
			-1);
	return (0);
}
