/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:36:16 by kipouliq          #+#    #+#             */
/*   Updated: 2024/01/11 16:36:38 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_lst	*node;
	t_lst	*new_lst;
	void	*temp;

	new_lst = NULL;
	while (lst)
	{
		temp = f(lst->content);
		node = ft_lstnew(temp);
		if (!node)
		{
			del(temp);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		lst = lst->next;
	}
	return (new_lst);
}

// t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_lst	*new_list;
// 	t_lst	*new_node;
// 	void	*set;

// 	if (!lst || !f || !del)
// 		return (NULL);
// 	new_list = NULL;
// 	while (lst)
// 	{
// 		set = f(lst->content);
// 		new_node = ft_lstnew(set);
// 		if (!new_node)
// 		{
// 			del(set);
// 			ft_lstdelone(new_list, (*del));
// 			return (new_list);
// 		}
// 		ft_lstadd_back(&new_list, new_node);
// 		lst = lst->next;
// 	}
// 	return (new_list);
// }
