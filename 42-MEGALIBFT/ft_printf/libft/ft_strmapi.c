/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:51:41 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/14 18:13:04 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*final_str;
	int		i;

	if (!s || !f)
		return (NULL);
	i = -1;
	final_str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!final_str)
		return (NULL);
	while (s[++i])
		final_str[i] = f(i, s[i]);
	final_str[i] = '\0';
	return (final_str);
}
