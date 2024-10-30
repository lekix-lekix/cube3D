/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:04:59 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/17 17:46:30 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	skip_elements(t_list **file_content)
{
	int	i;

	i = 0;
	while (file_content && i < 6)
	{
		if (!is_empty((*file_content)->content))
			i++;
		*file_content = (*file_content)->next;
	}
}

int	error_exit(char *str)
{
	printf("Error\n");
	if (str)
		printf("%s\n", str);
	exit(-1);
	return (-1);
}

int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr_until_idx(char **arr, int idx)
{
	int	i;

	i = -1;
	while (arr[++i] && i < idx)
		free(arr[i]);
}
