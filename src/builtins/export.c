/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:50 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/07 16:33:22 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_go(char **args, int i)
{
	char	*key;
	char	*val;

	key = get_key(args[i]);
	val = get_value(args[i]);
	add_global_venv(key, val, g_glob.venv);
}

void	check_plusegal(char *arg, t_m *m)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (arg[++i])
	{
		if (arg[i] != '+' && arg[i + 1] != '=')
			m->key[j] = arg[i];
		j++;
	}
}

void	addto_key(char *arg)
{
	t_m	m;

	m.key = get_key(arg);
	m.val = get_value(arg);
	gc_add_back(new_gcnode((void *)m.key));
	gc_add_back(new_gcnode((void *)m.val));
	m.key = malloc(ft_strlen(m.key));
	gc_add_back(new_gcnode((void *)m.key));
	check_plusegal(arg, &m);
	m.v = get_venv(m.key, g_glob.venv);
	if (m.v)
	{
		m.cokey = ft_strjoin(get_venv(m.key, g_glob.venv), m.val);
		add_global_venv(ft_strdup(m.key), m.cokey, g_glob.ennv);
		add_global_venv(ft_strdup(m.key), ft_strdup(m.cokey), g_glob.venv);
	}
	else
	{
		add_global_venv(ft_strdup(m.key), ft_strdup(m.val), g_glob.ennv);
		add_global_venv(ft_strdup(m.key), ft_strdup(m.val), g_glob.venv);
	}
}

void	check_args(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_isalpha(args[i][0]) || args[i][0] == '_')
		{
			if (if_egal(args[i]) && !if_plusegal(args[i]))
			{
				env_go(args[i]);
				export_go(args, i);
			}
			if (if_plusegal(args[i]))
				addto_key(args[i]);
			if (!if_egal(args[i]))
				export_go(args, i);
		}
		else
		{
			print_error_("export: `", args[i], "': not a valid identifier\n");
			g_glob.status = 1;
		}
		i++;
	}
}

void	export_cmd(char **args)
{
	if (!args[1])
	{
		sort_env(g_glob.venv);
		g_glob.status = 0;
	}
	else
		check_args(args);
}
