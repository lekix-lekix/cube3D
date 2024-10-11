/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:41:38 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/11 17:38:23 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../42-MEGALIBFT/megalibft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_window_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}   t_window_mlx;

typedef struct s_mlx_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_mlx_img;

// Map checking
int			check_sides_space(char **map, int i, int j);
int			is_map_char(char c);
int			is_player_direction(char c);
int			is_allowed_char(char c);
int			ft_is_space(char c);

// Minilibx display functions
int			start_mlx(int height, int width);

// Errror free function
int	error_exit(char *str);

#endif