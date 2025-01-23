/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuz_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:19 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/23 13:52:56 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
