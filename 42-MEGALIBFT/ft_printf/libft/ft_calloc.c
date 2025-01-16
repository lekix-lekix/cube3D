/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:30:53 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/15 13:48:43 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem_ptr;
	int		result;

	result = nmemb * size;
	if (size != 0 && result / size != nmemb)
		return (NULL);
	mem_ptr = malloc(nmemb * size);
	if (!mem_ptr)
		return (NULL);
	mem_ptr = ft_memset(mem_ptr, '\0', nmemb * size);
	return (mem_ptr);
}

// #include <limits.h>
// int main()
// {
	// char *str = ft_calloc(0, 5);
	// str[0] = 'l';
	// printf("%s\n", str);
// }