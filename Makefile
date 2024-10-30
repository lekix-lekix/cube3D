CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDE = cub3d.h
LIBFT = ./libft/libft.a
LIB = -L libft -lft -L mlx/ -lm
MLX = -lXext -lX11
NAME = cub3d
# NAME_BONUS = cub3d_bonus

SRC = src/parsing.c src/errors.c src/utils.c src/utils2.c src/init.c \
	src/add_text.c src/main.c src/get_color.c src/test_characters.c \
	src/map_checking.c \
	src/mlx.c \
	src/mlx_utils.c \
	src/handle_keyboard_inputs.c \
	src/movement_inputs.c \
	src/map_utils.c \
	src/minimap.c \
	src/bresenham.c
# SRC_BONUS =

OBJS_BASE = $(SRC:.c=.o)
# OBJS_BASE_BONUS = $(SRC_BONUS:.c=.o)
OBJ_PATH = obj/
OBJS = $(addprefix $(OBJ_PATH),$(OBJS_BASE))
# OBJS_BONUS = $(addprefix $(OBJ_PATH), $(OBJS_BASE_BONUS))

all: $(OBJ_PATH) $(NAME)

$(NAME) : $(OBJS)
	make -C libft/
	make -C mlx/
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L ./mlx -lmlx -lXext -lX11 -lm  -o $(NAME)

# $(NAME_BONUS) : $(OBJS_BONUS)
# 	make -C libft/
# 	make -C mlx/
# 	$(CC) $(CFLAGS) -I $(INCLUDE) $(MLX) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIB)

$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) -I ./libft -I ./mlx -c $< -o $@

$(OBJ_PATH):
	mkdir -p obj/
	mkdir -p obj/src/
#	mkdir -p obj/src_bonus/

clean:
	make fclean -C libft/
	rm -rf $(OBJ_PATH)
	rm -f $(OBJS)
#	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
#	rm -f $(NAME_BONUS)

re: fclean all

# bonus:	$(OBJ_PATH) $(NAME_BONUS)

.PHONY: all clean fclean re