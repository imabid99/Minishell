/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:26:41 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 01:16:23 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_glob = {.venv = NULL, .ennv = NULL, .vars = NULL,
	.status = 0, .io = {0}, .gc = NULL, .g = 0};

t_venv	**set_global_env(char **env, t_venv **ennv)
{
	int		len;
	t_venv	*new;
	char	*key;
	char	*value;

	ennv = init_venv(ennv);
	if (!env || !*env)
		return (ennv);
	len = 0;
	while (*(env + len))
	{
		key = get_key(*(env + len));
		value = get_value(*(env + len));
		new = new_venv(key, value);
		venv_add_back(ennv, new);
		gc_add_back(new_gcnode((void *)key));
		gc_add_back(new_gcnode((void *)value));
		len++;
	}
	return (ennv);
}

t_venv	**set_global_vars(t_venv **vars)
{
	vars = init_venv(vars);
	add_global_venv(ft_strdup("?"), ft_itoa(g_glob.status), vars);
	add_global_venv(ft_strdup("0"), ft_strdup("minishell"), vars);
	return (vars);
}

void	add_global_venv(char *key, char *value, t_venv **all)
{
	t_venv	*venv;
	char	*tmp;

	tmp = get_venv(key, all);
	if (!tmp)
	{
		venv = new_venv(key, value);
		venv_add_back(all, venv);
	}
	else if ((ft_strcmp(tmp, value)))
	{
		venv = *all;
		while (venv)
		{
			if (!ft_strcmp(key, venv -> key))
				venv -> value = value;
			venv = venv -> next;
		}		
	}
	gc_add_back(new_gcnode((void *)key));
	gc_add_back(new_gcnode((void *)value));
}

char	*get_venv(char *key, t_venv **all)
{
	t_venv	*venv;

	if (!*all)
		return (NULL);
	venv = *all;
	while (venv)
	{
		if (!ft_strcmp(venv -> key, key))
			return (venv -> value);
		venv = venv -> next;
	}
	return (NULL);
}

char	*get_var(char *key)
{
	t_venv	*var;

	var = *g_glob.vars;
	while (var)
	{
		if (!ft_strcmp(var -> key, key))
			return (var -> value);
		var = var -> next;
	}
	return (NULL);
}
