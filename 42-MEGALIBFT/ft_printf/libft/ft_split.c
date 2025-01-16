/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:39:41 by kipouliq          #+#    #+#             */
/*   Updated: 2024/01/22 17:55:15 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char sep)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == sep && s[i])
			i++;
		if (s[i] != sep && s[i])
			count++;
		while (s[i] != sep && s[i])
			i++;
	}
	return (count);
}

static char	*ft_malloc_cpy(char const *src, int n)
{
	char	*final_str;
	int		i;

	i = -1;
	final_str = malloc(sizeof(char) * (n + 1));
	if (!final_str)
		return (NULL);
	while (src[++i] && i < n)
		final_str[i] = src[i];
	final_str[i] = '\0';
	return (final_str);
}

static void	ft_skip(char const *str, int *i, char c, int skip_type)
{
	while ((skip_type && str[*i] == c) && str[*i])
		*i += 1;
	if (skip_type)
		return ;
	while ((!skip_type && str[*i] != c) && str[*i])
		*i += 1;
	if (!skip_type)
		return ;
}

static int	ft_fill_arr(char **strs, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = -1;
	while (s[i])
	{
		i = 0;
		ft_skip(s, &i, c, 1);
		if (!s[i])
			return (0);
		j = i;
		ft_skip(s, &j, c, 0);
		if (!s[j] || s[j] == c)
		{
			strs[++k] = ft_malloc_cpy(s + i, j - i);
			if (!strs[k])
				return (-1);
			if (!s[j])
				return (0);
			s += j;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	int		strs_count;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	strs_count = ft_count_words(s, c);
	if (!strs_count)
		return (NULL);
	str_arr = malloc(sizeof(char *) * (strs_count + 1));
	if (!str_arr)
		return (NULL);
	while (++i <= strs_count)
		str_arr[i] = NULL;
	if (ft_fill_arr(str_arr, s, c) == -1)
	{
		i = -1;
		while (++i <= strs_count)
			free(str_arr[i]);
		free(str_arr);
		return (NULL);
	}
	return (str_arr);
}

// int main ()
// {
// 	char **str = ft_split("a a a a a ", ' ');
// 	int i = -1;
// 	while (str && str[++i])
// 	{
// 		printf("str[%i] = %s\n", i, str[i]);
// 		free(str[i]);
// 	}
// 	free(str);
// 	(void) str;
// }