/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:38:10 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/11 20:41:49 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line.h"
# include <bsd/string.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_strlen(const char *str);
void				*ft_memset(void *str, int x, size_t n);
void				ft_bzero(void *str, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t n);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
int					ft_strncmpp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
void				*ft_memchr(const void *str, int to_find, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little, size_t n);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t nitems, size_t size);
char				*ft_strdup(const char *src);
char				*ft_substr(char const *str, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(const char *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				print_tab(char **tab);
int					size_tab(char **tab);
void				free_tab(char **tab);
void				ft_free(char *str);
int					free_list(t_list *list);

//  Bonus
t_list				*ft_lstnew(char *content);
int					ft_lstsize(t_list *lst);
int					ft_lstprint(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);

// GNL
char				*get_next_line(int fd, int flag);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_find(const char *str, int c);
char				*ft_strdup_gnl(const char *src);
int					ft_strlen_c(const char *str, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*add_to_buffer(char *buffer, char *line);
char				*copy_line(char *str);
char				*free_buffer(char *str);
char				*read_line(char *buffer, int fd);

#endif
