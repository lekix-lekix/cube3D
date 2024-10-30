/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:44:06 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/13 16:11:42 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_c(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	tab = malloc((ft_strlen_c(s1, '\0') + ft_strlen_c(s2, '\0') + 1)
			* sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j])
		tab[i++] = s2[j++];
	tab[i] = '\0';
	return (tab);
}

int	ft_find(const char *str, int c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == (char)c)
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (-1);
}

char	*ft_strdup_gnl(const char *src)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc((ft_strlen_c(src, '\0') + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strlen_c(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*result;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen_c(s, '\0'))
		return (ft_strdup_gnl(""));
	if ((ft_strlen_c(s, '\0') - start) <= len)
		len = ft_strlen_c(s, '\0') - start;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	while (len > 0)
	{
		result[i] = s[i + start];
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}
