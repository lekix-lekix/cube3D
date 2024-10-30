/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:46:51 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/27 17:08:38 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*result;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if ((ft_strlen(s) - start) <= len)
		len = ft_strlen(s) - start;
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

// int	main(void)
// {
// 	printf("ma fonction : %s", ft_substr("123456789", 3, 2));
// }
