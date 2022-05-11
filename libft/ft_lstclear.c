/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:51:36 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/18 17:33:34 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*first;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		first = *lst;
		*lst = (*lst)-> next;
		del(first -> content);
		free(first);
	}
}
