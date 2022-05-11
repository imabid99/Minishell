/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:30:47 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/08 20:08:40 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_err(char *arg)
{
	if (!ft_isdigit(arg[0]) && arg[0] != '-')
	{
		g_glob.status = 255;
		free_gc();
		exit(255);
	}
	exit(ft_atoi(arg));
}

void	check_num(char **args)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]) && args[1][0] != '-')
		{
			print_error_("exit: ", args[1],
				": numeric argument required\n");
			exit_err(args[i]);
		}
		i++;
	}
	if (!args[2])
		exit_err(args[1]);
}

void	exit_cmd(char **args)
{
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
	{
		free_gc();
		exit(g_glob.status);
	}
	if (args[1])
	{
		check_num(args);
	}
	if (args[2])
	{
		g_glob.status = 1;
		print_error_("exit", ": too many argument", "\n");
	}
}
