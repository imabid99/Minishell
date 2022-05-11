/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:39:03 by imabid            #+#    #+#             */
/*   Updated: 2022/04/29 15:42:48 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_egal(char *arg)
{
	int				i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	if_plusegal(char *arg)
{
	int				i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export_print(t_venv **ve)
{
	t_venv	*venv;

	venv = *ve;
	while (venv)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(venv->key, 1);
		if (*venv->value != '\0')
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd(venv->value, 1);
		if (*venv->value != '\0')
		{
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		venv = venv->next;
	}
}

void	sort_env( t_venv **venv)
{
	char	*tmp;
	char	*tmpv;
	t_venv	*j;
	t_venv	*i;

	i = *venv;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
			{
				tmp = i -> key;
				i -> key = j -> key;
				j -> key = tmp;
				tmpv = i -> value;
				i -> value = j -> value;
				j -> value = tmpv;
			}
			j = j->next;
		}
		i = i->next;
	}
	export_print(venv);
}
