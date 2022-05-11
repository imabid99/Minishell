/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:56 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 01:32:10 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unvalid_arg(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if (ft_isalpha(arg[i]) || arg[i] == '_')
	{
		while (arg[++i])
			if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
				return (0);
		return (1);
	}
	return (0);
}

void	unset_cmd(char **args)
{
	int	i;

	i = 0;
	g_glob.status = 0;
	while (args[++i])
	{
		if (!unvalid_arg(args[i]))
		{
			print_error_("unset: `", args[i], "': not a valid identifier\n");
			g_glob.status = 1;
			continue ;
		}
		del_venv(args[i]);
		del_ennv(args[i]);
	}
}
