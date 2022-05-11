/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:30:04 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/18 17:33:44 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*elem;
	t_list	*first;

	if (!lst || !f)
		return (NULL);
	elem = ft_lstnew(f(lst -> content));
	if (!elem)
		return (NULL);
	newlst = elem;
	first = newlst;
	lst = lst -> next;
	while (lst)
	{
		elem = ft_lstnew(f(lst -> content));
		if (!elem)
		{
			ft_lstclear(&newlst, del);
			break ;
		}
		newlst -> next = elem;
		newlst = elem;
		lst = lst -> next;
	}
	return (first);
}
