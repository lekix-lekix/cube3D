CC = cc
CFLAGS = -Wall -Wextra  -Werror -g3
INCLUDE = libft.h
NAME = libft.a

SRC = ft_isalpha.c ft_strncmpp.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
    ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
    ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strcmp.c \
    ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
    ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
    ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
    get_next_line.c get_next_line_utils.c tab_utils.c \
    free.c list_utils.c\

OBJS_BASE = $(SRC:.c=.o)
OBJ_PATH = lib_obj/
OBJS = $(addprefix $(OBJ_PATH),$(OBJS_BASE))

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p lib_obj/

clean:
	rm -rf $(OBJ_PATH)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
