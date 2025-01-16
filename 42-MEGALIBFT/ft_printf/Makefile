# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 14:33:33 by lekix             #+#    #+#              #
#    Updated: 2024/01/11 18:23:23 by kipouliq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a

SRC = ft_printf.c \
	func_calls_nb.c \
	func_calls_hex.c \
	func_calls_chr.c \
	ft_putnbr.c \
	ft_putnbr_base.c \
	conversions.c \
	utils.c

OBJ = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror -g

PATH_LIBFT = ./libft

all : bonus

$(NAME) : $(OBJ)
	make -C $(PATH_LIBFT)
	cp ./libft/libft.a ./libftprintf.a
	ar -rcs $@ $(OBJ)

bonus : $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -I $(PATH_LIBFT) -o $@

clean :
	make -sC $(PATH_LIBFT) clean
	rm -f *o

fclean : clean
	make -sC $(PATH_LIBFT) fclean
	rm -f $(NAME)

re : fclean
	make all

.PHONY : all bonus clean fclean re