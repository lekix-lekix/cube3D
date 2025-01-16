/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:22:23 by kipouliq          #+#    #+#             */
/*   Updated: 2024/08/28 14:39:05 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_str_cpy(char const *s, char *sub_str, size_t len, size_t start)
{
	size_t	i;

	i = -1;
	while (s[++i] && i < len && s[start])
	{
		sub_str[i] = s[start];
		start++;
	}
	sub_str[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*sub_str;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len || len == 0)
	{
		sub_str = malloc(1);
		sub_str[0] = '\0';
		// free((char *)s);
		return (sub_str);
	}
	if (len > str_len)
		sub_str = malloc(sizeof(char) * (str_len + 1));
	else if (len < str_len)
		sub_str = malloc(sizeof(char) * (len + 1));
	else
		sub_str = malloc(sizeof(char) * (str_len - start + 1));
	if (!sub_str)
		return (NULL);
	ft_str_cpy(s, sub_str, len, start);
	// free((char *)s);
	return (sub_str);
}

// #include <string.h>

// int main()
// {
// 	char *str2 = ft_substr("tripouille", 0, 42000);
// 	printf("%s\n", str2);
// 	free(str2);

// }