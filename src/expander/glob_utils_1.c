/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:25:05 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/07 01:08:31 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *env)
{
	int		len;
	char	*s;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	s = ft_strndup(env, len + 1);
	return (s);
}

char	*get_value(char *env)
{
	int		len;
	char	*s;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	s = ft_strdup(env + len + 1);
	return (s);
}

t_venv	**init_venv(t_venv **venv)
{
	venv = malloc(sizeof(t_venv));
	gc_add_back(new_gcnode((void *)venv));
	if (!venv)
		return (NULL);
	*venv = NULL;
	return (venv);
}

t_venv	*new_venv(char *key, char *value)
{
	t_venv	*venv;

	venv = malloc(sizeof(t_venv) * 1);
	gc_add_back(new_gcnode((void *)venv));
	if (!venv)
		return (NULL);
	venv -> key = key;
	venv -> value = value;
	venv -> next = NULL;
	return (venv);
}

void	venv_add_back(t_venv **venv, t_venv *new)
{
	t_venv	*first;

	if (!venv)
		return ;
	if (!*venv)
		*venv = new;
	else
	{
		first = *venv;
		while (first -> next != NULL)
			first = first -> next;
		first -> next = new;
	}
}
