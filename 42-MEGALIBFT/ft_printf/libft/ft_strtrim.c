/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:55:50 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/15 10:08:07 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

static int	ft_total_to_trim(char const *str, char const *set, int *begin)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (ft_is_in_set(str[++i], set))
		count++;
	*begin = i;
	i = ft_strlen(str);
	while (ft_is_in_set(str[--i], set))
		count++;
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		str_size;
	char	*final_str;

	if (!s1 || !set)
		return (NULL);
	str_size = ft_strlen(s1) - ft_total_to_trim(s1, set, &i) + 1;
	if (str_size < 0)
	{
		final_str = malloc(1);
		final_str[0] = '\0';
		return (final_str);
	}
	final_str = malloc(sizeof(char) * str_size);
	if (!final_str)
		return (NULL);
	j = 0;
	while (s1[i] && j < str_size - 1)
	{
		final_str[j] = s1[i++];
		j++;
	}
	final_str[j] = '\0';
	return (final_str);
}

// int main()
// {
// 	char *str ="   xxx   xxx";
// 	char *str2 = ft_strtrim(str, " x");
// 	if (!str2)
// 		return (-1);
// 	printf("'%s'\n", str2);
// 	free(str2);
// }