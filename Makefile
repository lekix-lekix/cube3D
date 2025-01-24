# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 14:55:41 by sabakar-          #+#    #+#              #
#    Updated: 2025/01/24 14:06:54 by kipouliq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

INCLUDE = cub3d.h
PATH_LIBFT = ./42-MEGALIBFT
LIBFT = ./42-MEGALIBFT/megalibft.a
MLX_INC = -L ./mlx -lmlx -lXext -lX11 -lm

NAME = cub3d
NAME_BONUS = cub3d_bonus

SRC_BASE = src/errors.c \
	src/utils.c \
	src/utils2.c \
	src/init.c \
	src/get_color.c \
	src/map_checking.c \
	src/map_drawing_bis.c \
	src/maths_vectors_bis.c \
	src/mlx_utils.c \
	src/movement.c \
	src/map_utils.c \
	src/map_drawing.c \
	src/bresenham.c \
	src/wall_collisions.c \
	src/raycasting_bis.c \
	src/rendering.c \
	src/colors_rendering.c \
	src/maths_vectors.c \
	src/textures.c \
	src/exit_free.c \
	src/ft_file_checking.c \
	src/ft_get_textures.c \
	src/another_utils.c \
	src/cuz_norm.c

SRC_MAND = src/main.c \
	src/handle_keyboard_inputs.c \
	src/raycasting.c \
	src/test_characters.c

SRC_BONUS = src/main_bonus.c \
	src/handle_keyboard_inputs_bonus.c \
	src/raycasting_bonus.c \
	src/test_characters_bonus.c \
	src/doors_bonus.c

OBJ_PATH = obj/
OBJS_BASE = $(SRC_BASE:.c=.o)
OBJS_MAND = $(SRC_MAND:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

RUN_OBJS_BASE = $(addprefix $(OBJ_PATH),$(OBJS_BASE))
RUN_OBJS_MAND = $(addprefix $(OBJ_PATH),$(OBJS_MAND))
RUN_OBJS_BONUS = $(addprefix $(OBJ_PATH),$(OBJS_BONUS))

OBJS = $(RUN_OBJS_BASE) $(RUN_OBJS_MAND)

all: $(OBJ_PATH) $(NAME)

$(NAME): $(RUN_OBJS_BASE) $(RUN_OBJS_MAND)
	make -C $(PATH_LIBFT)
	make -C mlx/
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_INC) -o $(NAME)

bonus: $(OBJ_PATH) $(NAME_BONUS)

$(NAME_BONUS): $(RUN_OBJS_BASE) $(RUN_OBJS_BONUS)
	make -C $(PATH_LIBFT)
	make -C mlx/
	$(CC) $(CFLAGS) $(RUN_OBJS_BASE) $(RUN_OBJS_BONUS) $(LIBFT) $(MLX_INC) -o $(NAME_BONUS)

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(PATH_LIBFT) -I ./mlx -c $< -o $@

$(OBJ_PATH):
	mkdir -p obj/
	mkdir -p obj/src/

clean:
	make -sC $(PATH_LIBFT) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -sC $(PATH_LIBFT) fclean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus