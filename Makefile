# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 14:55:41 by sabakar-          #+#    #+#              #
#    Updated: 2025/01/16 11:48:49 by sabakar-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDE = cub3d.h

PATH_LIBFT = ./42-MEGALIBFT
LIBFT = ./42-MEGALIBFT/megalibft.a

# LIB = -L libft -lft -L mlx/ -lm
MLX = -lXext -lX11
NAME = cub3d
# NAME_BONUS = cub3d_bonus

SRC = src/errors.c src/utils.c src/utils2.c src/init.c \
	src/main.c src/get_color.c src/test_characters.c \
	src/map_checking.c \
	src/map_drawing_bis.c \
	src/maths_vectors_bis.c \
	src/mlx_utils.c \
	src/handle_keyboard_inputs.c \
	src/movement.c \
	src/map_utils.c \
	src/map_drawing.c \
	src/bresenham.c \
	src/wall_collisions.c \
	src/raycasting.c \
	src/raycasting_bis.c \
	src/rendering.c \
	src/colors_rendering.c \
	src/maths_vectors.c \
	src/textures.c \
	src/doors.c \
	src/exit_free.c \
	src/ft_file_checking.c \
	src/ft_get_textures.c \
	src/another_utils.c

OBJS_BASE = $(SRC:.c=.o)
# OBJS_BASE_BONUS = $(SRC_BONUS:.c=.o)
OBJ_PATH = obj/
OBJS = $(addprefix $(OBJ_PATH),$(OBJS_BASE))
# OBJS_BONUS = $(addprefix $(OBJ_PATH), $(OBJS_BASE_BONUS))

all: $(OBJ_PATH) $(NAME)

$(NAME) : $(OBJS)
	make -C $(PATH_LIBFT)
	make -C mlx/
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L ./mlx -lmlx -lXext -lX11 -lm  -o $(NAME)

# $(NAME_BONUS) : $(OBJS_BONUS)
# 	make -C libft/
# 	make -C mlx/
# 	$(CC) $(CFLAGS) -I $(INCLUDE) $(MLX) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIB)

$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) -I $(PATH_LIBFT) -I ./mlx -c $< -o $@

$(OBJ_PATH):
	mkdir -p obj/
	mkdir -p obj/src/
#	mkdir -p obj/src_bonus/

clean:
	make -sC $(PATH_LIBFT) clean
	rm -rf $(OBJ_PATH)
	rm -f $(OBJS)
#	rm -f $(OBJS_BONUS)

fclean: clean
	make -sC $(PATH_LIBFT) fclean
	rm -f $(NAME)
#	rm -f $(NAME_BONUS)

re: fclean all

# bonus:	$(OBJ_PATH) $(NAME_BONUS)

.PHONY: all clean fclean re