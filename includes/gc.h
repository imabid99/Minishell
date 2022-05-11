/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:09:57 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/07 16:40:36 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

typedef struct s_gc
{
	void		*s;
	struct s_gc	*next;
}	t_gc;

t_gc	**init_gc(void);
t_gc	*new_gcnode(void *str);
char	*gc_add_back(t_gc *new);
void	free_gc(void);

#endif
