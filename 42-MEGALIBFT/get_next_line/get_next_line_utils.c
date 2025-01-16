/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:42:51 by kipouliq          #+#    #+#             */
/*   Updated: 2024/01/16 17:13:43 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

char	*something_happened(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (NULL);
}

size_t	ft_strlen_2(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*final_str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1)
		return (s2);
	s1_size = ft_strlen_2(s1);
	s2_size = ft_strlen_2(s2);
	final_str = malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (!final_str)
		return (something_happened(s1, s2));
	while (s1[++i])
		final_str[i] = s1[i];
	while (s2[++j])
	{
		final_str[i] = s2[j];
		i++;
	}
	final_str[i] = '\0';
	s1 = something_happened(s1, s2);
	return (final_str);
}

int	check_static_str(char *static_str, char **eol, int *b_read, int free_static)
{
	int	i;

	i = -1;
	*eol = NULL;
	if (free_static)
	{
		*eol = NULL;
		*b_read = 0;
		something_happened(static_str, NULL);
		return (1);
	}
	if (!static_str)
		return (0);
	while (static_str[++i])
	{
		if (static_str[i] == '\n')
		{
			*eol = static_str + i;
			break ;
		}
	}
	if (*eol)
		return (1);
	else
		return (0);
}

char	*get_nbytes(int fd, int *bytes_read)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (something_happened(str, NULL));
	while (++i < BUFFER_SIZE + 1)
		str[i] = '\0';
	*bytes_read = read(fd, str, BUFFER_SIZE);
	if (*bytes_read == -1)
		return (something_happened(str, NULL));
	return (str);
}
