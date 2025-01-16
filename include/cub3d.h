/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:56:50 by sabakar-          #+#    #+#             */
/*   Updated: 2025/01/16 16:53:07 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../42-MEGALIBFT/megalibft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 800
# define W 119
# define A 97
# define S 115
# define D 100
# define F 102
# define P 112
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define ESCAPE 65307
# define FOV 60
# define PI 3.14159265359
# define PI_RAD 0.01745329251
# define MEM_ERROR "Memory allocation failed"

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

typedef struct s_movements
{
	bool			fwd;
	bool			bwd;
	bool			strafe_l;
	bool			strafe_r;
	bool			dir_l;
	bool			dir_r;
	int				buffer;
}					t_movements;

typedef struct s_ray
{
	double			length;
	double			intersection_x;
	double			intersection_y;
	double			angle;
	double			angle_inc;
	double			relative_angle;
	double			proj_height;
	double			distance_to_proj_plane;
}					t_ray;

typedef struct s_dda_vars
{
	double			dx;
	double			dx_sum;
	double			dy;
	double			dy_sum;
	int				x;
	int				y;
}					t_dda_vars;

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
	char			initial_dir;
	double			angle;
}					t_player;

typedef struct s_color
{
	int				t;
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_texture
{
	t_mlx_img		*text_img;
	int				width;
	int				height;
}					t_texture;

typedef struct s_texture_slice
{
	t_texture		*texture;
	double			idx_x;
	double			idx_y;
	double			scaling;
}					t_texture_slice;

typedef struct s_cub
{
	t_texture		*no_text;
	t_texture		*so_text;
	t_texture		*ea_text;
	t_texture		*we_text;
	t_texture		*door_text;
	t_texture		*sky;
	int				map_unit;
	bool			sky_bool;
	t_color			c_color;
	t_color			f_color;
	char			**map;
	t_movements		mov;
	t_window_mlx	mlx_data;
	t_player		player;
}					t_cub;

// Map checking
char				**get_map(t_cub *cub, t_lst **file);
int					check_map(t_cub *cub);
int					check_sides_space(char **map, int i, int j);
int					is_map_char(char c);
int					is_player_direction(char c);
int					is_allowed_char(char c);
int					ft_is_space(char c);

// Map
int					draw_map(t_mlx_img *img, t_cub *cub);
void				find_player_init_pos(t_cub *cub);
int					draw_map_rays(t_mlx_img *img, t_cub *cub,
						t_vector *map_rays);
int					draw_line(t_position start, t_position end, int color,
						t_mlx_img *img);

// Map utils
void				free_arr_until_idx(char **arr, int idx);
int					get_arr_size(char **arr);
t_lst				*skip_elements(t_lst **file_content);

// Minilibx display functions
int					start_mlx(int height, int width, t_cub *cub);
t_mlx_img			*init_img(t_window_mlx *data, t_cub *cub);
int					*get_pixel_from_img(t_mlx_img *img, int x, int y);
void				img_pix_put(t_mlx_img *img, int x, int y, int color);
t_texture			*init_mlx_img_texture(t_cub *cub, char *path);
int					ft_check_textures(char **tab, t_cub *cub,
						t_texture **cub_text);

// Colors rendering
int					create_trgb(int t, int r, int g, int b);
t_color				extract_rgb(int color_int);
int					create_trgb_struct(t_color color);
int					create_shaded_color(t_ray *ray, t_color color);

// Texturing
void				pick_texture_slice(t_cub *cub, t_ray *ray,
						t_texture_slice *slice);
int					pick_slice_color(t_texture_slice *slice, t_ray *ray, int i,
						int start_y_px);

// Raycasting
int					start_raycasting(t_cub *cub);
int					refresh_raycasting(t_cub *cub);
double				find_ray_length(t_cub *cub, t_ray *ray);
int					check_wall_collision(t_cub *cub, char dir);
double				find_ray_length(t_cub *cub, t_ray *ray);
void				init_dx_dy(t_dda_vars *vars, double angle);
double				wall_hit(t_ray *ray, t_position player_pos, t_dda_vars vars,
						int last_hit);

// Rendering
int					draw_vertical_slice(t_mlx_img *img, t_cub *cub, int x,
						t_ray *ray);

// Handle keyboard inputs
int					handle_keypress(int key, t_cub *cub);
int					handle_keyrelease(int key, t_cub *cub);

// Maths & vectors
double				degree_to_rad(double degree);
t_position			get_pos_from_vector(t_position init_pos, t_vector vector);
double				wrap_angle_360(double angle, double change, bool add);
t_vector			rotate_vector(t_vector vec, double angle);
t_vector	get_vector_from_length(double ray_length,
								double degree_angle);
t_position			coordinates_to_px(t_cub *cub, double x, double y);
t_vector			find_dir(t_cub *cub);

// Movement inputs
int					check_player_movements(t_cub *cub);
int					move_character_in_direction(int key, t_cub *cub);
int					strafe(int right, t_cub *cub);
int					move_direction_left(t_cub *cub);
int					move_direction_right(t_cub *cub);
int					open_close_door(t_cub *cub);

// Free functions
int					error_exit(char *str, t_cub *cub);
void				err_map_not_valid(int err);
void				destroy_free_texture(t_cub *cub, t_texture *texture);
int					quit_cube(t_cub *cub);
int					handle_destroy(t_cub *cub);
int					free_list(t_lst *list);
void				ft_free(char *str);
void				free_line(char *line);
void				free_cub(t_cub *cub);
void				ft_free_and_return(char **split_elem, t_cub *cub);
void				tab_free(char **tab);

// init
void				init_cub(t_cub *cub);
void				init_mov(t_cub *cub);

// add text
void				add_texture(char **split_elem, t_lst *file_content,
						t_cub *cub);

// get color
void				ft_get_color(char **tab, t_cub *cub, char id);

// utils
bool				is_space(char c);
bool				is_empty(char *str);
int					is_elem(char *str);
int					size_tab(char **tab);

// utils2
bool				is_number(char c);
bool				only_numbers(char *str);
int					create_rgb(int r, int g, int b);
int					pos_atoi(char *str);
// void				skip_elements(t_lst **file_content);
// void	ft_destroy_cub(t_cub cub);

// errors
void				map_error(int fd, char *msg, t_lst *file_content);
void				texture_error(char **tab, t_cub *cub, char *msg);
void				color_error(char **tab, t_cub *cub, char *color);

// ft_split
char				**ft_split(const char *s, char c);

// parsing
int					ft_read_file(char *file_path, t_cub *cub);
int					ft_check_extension(char *sr);
int					get_elems(t_lst *file_content, t_cub *cub);
void				ft_another_function(t_cub *cub);

#endif