/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:54:49 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/08 00:14:34 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_venv(char *key)
{
	t_venv	*venv;
	t_venv	*vnext;

	venv = *g_glob.venv;
	if (!ft_strcmp(key, venv -> key))
	{
		*g_glob.venv = (*g_glob.venv)-> next;
		free (venv);
	}
	else
	{
		while (venv -> next)
		{
			vnext = venv -> next;
			if (!ft_strcmp(key, vnext -> key))
				break ;
			venv = venv -> next;
		}
		venv -> next = vnext -> next;
	}
}

char	*get_venv_all(char *key)
{
	char	*value;

	value = get_venv(key, g_glob.vars);
	if (!value)
		value = get_venv(key, g_glob.venv);
	if (!value)
		value = get_venv(key, g_glob.ennv);
	if (!value)
		return (NULL);
	return (value);
}

void	del_ennv(char *key)
{
	t_venv	*venv;
	t_venv	*vnext;

	venv = *g_glob.ennv;
	if (!ft_strcmp(key, venv -> key))
	{
		*g_glob.ennv = (*g_glob.ennv)-> next;
		free (venv);
	}
	else
	{
		while (venv -> next)
		{
			vnext = venv -> next;
			if (!ft_strcmp(key, vnext -> key))
				break ;
			venv = venv -> next;
		}
		venv -> next = vnext -> next;
	}
}
