/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:41:41 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/13 16:09:55 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd, int flag);
char	*ft_strjoin_c(char const *s1, char const *s2);
int		ft_find(const char *str, int c);
char	*ft_strdup_gnl(const char *src);
int		ft_strlen_c(const char *str, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*add_to_buffer(char *buffer, char *line);
char	*copy_line(char *str);
char	*free_buffer(char *str);
char	*read_line(char *buffer, int fd);

#endif