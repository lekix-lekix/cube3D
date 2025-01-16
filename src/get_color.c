/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:49:03 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/16 12:06:49 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_parse_color(char *color_str, int *red, int *green, int *blue,
			t_cub *cub);
void	ft_set_color(t_cub *cub, char id, int red, int green, int blue);

void	ft_get_color(char **tab, t_cub *cub, char id)
{
	char	*color;
	int		red;
	int		green;
	int		blue;

	if (!tab || size_tab(tab) != 2)
		return (texture_error(tab, cub, "Format error. Example: C 225,30,0"));
	color = ft_strtrim(tab[1], "\n");
	if (!color)
		return (color_error(tab, cub, NULL));
	if (ft_parse_color(color, &red, &green, &blue, cub) == -1)
		return (ft_free(color));
	ft_set_color(cub, id, red, green, blue);
	// if (id == 'C')
	// {
	// 	cub->c_color.r = red;
	// 	cub->c_color.g = green;
	// 	cub->c_color.b = blue;
	// }
	// else if (id == 'F')
	// {
	// 	cub->f_color.r = red;
	// 	cub->f_color.g = green;
	// 	cub->f_color.b = blue;
	// }
	ft_free(color);
}

void	ft_set_color(t_cub *cub, char id, int red, int green, int blue)
{
	if (id == 'C')
	{
		cub->c_color.r = red;
		cub->c_color.g = green;
		cub->c_color.b = blue;
	}
	else if (id == 'F')
	{
		cub->f_color.r = red;
		cub->f_color.g = green;
		cub->f_color.b = blue;
	}
}

int	ft_parse_color(char *color_str, int *red, int *green, int *blue, t_cub *cub)
{
	char **rgb;

	rgb = ft_split(color_str, ',');
	if (!rgb)
		return (color_error(NULL, cub, color_str), -1);
	*red = pos_atoi(rgb[0]);
	*green = pos_atoi(rgb[1]);
	*blue = pos_atoi(rgb[2]);
	tab_free(rgb);
	if (*red < 0 || *green < 0 || *blue < 0)
		return (texture_error(NULL, cub,
				"Format error. It should contain something like this: C 225,30,0"),
			-1);
	return (0);
}

// char	**ft_split_this_shit(char *color_str)
// {
	
// }