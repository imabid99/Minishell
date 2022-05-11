/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:47:17 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/08 00:43:04 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc	**init_gc(void)
{
	t_gc	**gc;

	gc = malloc(sizeof(t_gc *));
	*gc = NULL;
	return (gc);
}

t_gc	*new_gcnode(void *str)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	gc->s = str;
	gc -> next = NULL;
	return (gc);
}

char	*gc_add_back(t_gc *new)
{
	t_gc	*first;
	t_gc	**gc;

	gc = g_glob.gc;
	if (!gc)
		return (NULL);
	if (*gc)
	{
		first = *gc;
		while (first -> next)
			first = first -> next;
		first -> next = new;
	}
	else
		*gc = new;
	return ((char *)new -> s);
}

void	free_gc(void)
{
	t_gc	*g;
	t_gc	*t;

	g = *g_glob.gc;
	while (g)
	{
		t = g -> next;
		if (g -> s != NULL)
			free(g->s);
		g -> s = NULL;
		free(g);
		g = NULL;
		g = t;
	}
	free(g_glob.gc);
	g_glob.gc = NULL;
}
