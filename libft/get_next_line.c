/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:16:43 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/13 16:10:29 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*add_to_buffer(char *buffer, char *line)
{
	char	*temp;

	temp = ft_strjoin_c(buffer, line);
	free(buffer);
	return (temp);
}

char	*copy_line(char *str)
{
	char	*final;

	if (!str[0])
		return (NULL);
	if (ft_strlen_c(str, '\n') >= 0)
		final = ft_substr(str, 0, ft_strlen_c(str, '\n') + 1);
	else if (ft_strlen_c(str, '\0') > 0)
		final = ft_substr(str, 0, (ft_strlen_c(str, '\0') + 1));
	else
		final = ft_substr(str, 0, ft_strlen_c(str, '\0') + 1);
	return (final);
}

char	*free_buffer(char *str)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	next_line = (char *)malloc(sizeof(char) * (ft_strlen_c(str, '\0') - i + 1));
	if (!next_line)
		return (NULL);
	i++;
	while (str[i])
		next_line[j++] = str[i++];
	next_line[j] = '\0';
	free(str);
	return (next_line);
}

char	*read_line(char *buffer, int fd)
{
	int		bytes;
	char	*line;

	bytes = 1;
	if (!buffer)
	{
		buffer = malloc(sizeof(char));
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (bytes > 0)
	{
		bytes = read(fd, line, BUFFER_SIZE);
		if (bytes < 0)
			return (free(line), NULL);
		line[bytes] = '\0';
		buffer = add_to_buffer(buffer, line);
		if (ft_find(line, '\n') == 1)
			break ;
	}
	return (free(line), buffer);
}

char	*get_next_line(int fd, int flag)
{
	char		*res;
	static char	*buffer;

	if (flag == 1)
	{
		free(buffer);
		return (NULL);
	}
	if ((fd < 0) || (BUFFER_SIZE <= 0) || (read(fd, 0, 0) < 0))
		return (NULL);
	buffer = read_line(buffer, fd);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	res = copy_line(buffer);
	buffer = free_buffer(buffer);
	return (res);
}

// int	main(void)
// {
// 	int fd;
// 	int i;
// 	char *str;

// 	i = 0;
// 	while (i < 100)
// 	{
// 		str = get_next_line(0);
// 		if (str == NULL)
// 			break ;
// 		printf("%s\n", str);
// 		free(str);
// 		i++;
// 	}
// }