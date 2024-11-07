/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:14:10 by inbennou          #+#    #+#             */
/*   Updated: 2024/11/07 18:28:38 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define ESCAPE 65307
# define ONE_UNIT 120
# define FOV 60
# define PI 3.14159265359
# define PI_RAD 0.01745329251

typedef struct s_window_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
}					t_window_mlx;

typedef struct s_mlx_img
{
	void			*img_ptr;
	char			*img_addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_mlx_img;

typedef struct s_position
{
	double			x;
	double			y;
}					t_position;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_player
{
	t_position		pos;
	t_vector		dir;
	t_vector		fov_l;
	t_vector		fov_r;
    char            initial_dir;
	double			angle;
}					t_player;

typedef struct s_cub
{
	char			*no_text;
	char			*so_text;
	char			*ea_text;
	char			*we_text;
	int				c_color;
	int				f_color;
	char			**map;
	t_window_mlx	mlx_data;
	t_player		player;
}					t_cub;

// Map checking
char				**get_map(t_list **file);
int					check_map(t_cub *cub);
int					check_sides_space(char **map, int i, int j);
int					is_map_char(char c);
int					is_player_direction(char c);
int					is_allowed_char(char c);
int					ft_is_space(char c);

// Minilibx display functions
int					start_mlx(int height, int width, t_cub *cub);
t_mlx_img			*init_img(t_window_mlx *data);
void				img_pix_put(t_mlx_img *img, int x, int y, int color);
void				drawLine(int x0, int y0, int x1, int y1, int c,
						t_mlx_img *img);

// Raycasting
int					start_raycasting(t_window_mlx *data, t_cub *cub);
int					refresh_raycasting(t_cub *cub);
t_vector			rotate_vector(t_vector vec, double angle);
t_position			get_pos_from_vector(t_position init_pos, t_vector vector);
double				degree_to_rad(int degree);

// Handle keyboard inputs
int					handle_keyboard_inputs(int key, t_cub *cub);

// Movement inputs
int					move_character_up(t_cub *cub);
int					move_character_down(t_cub *cub);
int					move_character_left(t_cub *cub);
int					move_character_right(t_cub *cub);

// Free functions
int					quit_cube(t_cub *cub);
int					error_exit(char *str);
void				exit_map_not_valid(t_cub *cub, int err);

// Map
int					draw_map(t_mlx_img *img, char **map);

// Map utils
void				free_arr_until_idx(char **arr, int idx);
int					get_arr_size(char **arr);
void				skip_elements(t_list **file_content);

// parsing
void				name_check(char *str);
t_list				*get_file(int fd);
void				elems_check(char **split_elem, t_list *start, t_cub *cub);
bool				get_elems(t_list *file_content, t_cub *cub, t_list *start);
void				parsing(int ac, char **av, t_list **start, t_cub *cub);

// init
void				init_cub(t_cub *cub);

// add text
void				add_texture(char **split_elem, t_list *file_content,
						t_list *start, t_cub *cub);
int					add_north(char **tab, t_list *start, t_cub *cub);
int					add_south(char **tab, t_list *start, t_cub *cub);
int					add_east(char **tab, t_list *start, t_cub *cub);
int					add_west(char **tab, t_list *start, t_cub *cub);

// get color
int					get_int(char **split_elem, t_list *start, t_cub *cub,
						char *color);
void				get_color(char **split_elem, t_list *start, t_cub *cub,
						char id);

// utils
bool				is_space(char c);
void				free_line(char *line);
void				free_cub(t_cub *cub);
bool				is_empty(char *str);
bool				is_elem(char *str);

// utils2
bool				is_number(char c);
bool				only_numbers(char *str);
int					create_rgb(int r, int g, int b);
int					pos_atoi(char *str);
void				skip_elements(t_list **file_content);

// errors
void				map_error(int fd, char *msg, t_list *file_content);
void				texture_error(char **tab, t_list *start, t_cub *cub,
						char *msg);
void				color_error(char **tab, t_list *start, t_cub *cub,
						char *color);

// ft_split
char				**ft_split(const char *s, char c);

#endif