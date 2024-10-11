# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 14:45:02 by kipouliq          #+#    #+#              #
#    Updated: 2024/10/11 16:39:43 by kipouliq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3D

SRCS = ./srcs/map/map_checking.c \
	./srcs/map/test_characters.c \
	./srcs/mlx/mlx.c

OBJ = $(SRCS:.c=.o)

OBJ_BONUS = $(SRCS_BONUS:.c=.o)

INCLUDE = -I

CC = cc

MLX = ./minilibx-linux/libmlx.a

MLX_FLAGS = -lmlx -lXext -lX11 -lm 

FLAGS = -Wall -Wextra -Werror -g3

PATH_LIBFT = ./42-MEGALIBFT

PATH_MLX = ./minilibx-linux

LIBFT = ./42-MEGALIBFT/megalibft.a

all :
	git submodule update --init
	make $(NAME)

$(NAME) : $(OBJ)
	make -C $(PATH_MLX)
	make -C $(PATH_LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -L ./minilibx-linux $(MLX_FLAGS) -o $(NAME) -g3

%.o:%.c
	$(CC) $(FLAGS) -I $(PATH_LIBFT) -I $(PATH_MLX) -c $< -o $@

clean :
	make -sC $(PATH_MLX) clean
	make -sC $(PATH_LIBFT) clean
	rm -f ./srcs/*/*.o
	
fclean : clean
	make -sC $(PATH_LIBFT) fclean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re : fclean
	make all

.PHONY : all bonus clean fclean re