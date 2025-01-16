/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:12:27 by kipouliq          #+#    #+#             */
/*   Updated: 2024/05/09 16:14:07 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstfind_node(t_lst **list, void *mem_addr)
{
	t_lst	*node;

	node = *list;
	while (node)
	{
		if (node->content == mem_addr)
			return (node);
		node = node->next;
	}
	return (NULL);
}
