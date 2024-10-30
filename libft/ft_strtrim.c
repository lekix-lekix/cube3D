/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:07:45 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/27 17:34:39 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_set(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*tab;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	k = 0;
	while (s1[i] && find_set(set, s1[i]))
		i++;
	while ((j > i) && find_set(set, s1[j - 1]))
		j--;
	tab = malloc((j - i + 1) * sizeof(char));
	if (!tab)
		return (0);
	while (i < j)
	{
		tab[k] = s1[i];
		i++;
		k++;
	}
	tab[k] = '\0';
	return (tab);
}

// int	main(void)
// {
// 	printf("%s", ft_strtrim("Hello world!    xxx", " x"));
// }
