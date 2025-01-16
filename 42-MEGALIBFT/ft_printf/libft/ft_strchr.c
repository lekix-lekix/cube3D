/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:51 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/14 18:18:03 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == (char) c)
			return ((char *)s + i);
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

	// #include <string.h>

	// int main()
	// {
	//     char s[] = "tripouille";
	//     printf("%c\n", 't' + 256);
	//     printf("%s\n", ft_strchr(s, 't' + 256));
	//     printf("%s\n", strchr(s, 't' + 256));
	// }