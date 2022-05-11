/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 20:51:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 01:05:12 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT && !g_glob.g)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_glob.status = 1;
	}
}

static int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ctrl_d(void)
{
	char	*sr_cap;

	sr_cap = tgetstr("sr", NULL);
	tputs(sr_cap, 0, ft_putchar);
	ft_putstr_fd("minishell$ exit\n", 1);
	exit(g_glob.status);
}

void	signal_handl(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, sig_handler);
	return ;
}

int	ft_statushundling(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			write(2, "Quit: 3\n", 8);
		if (WTERMSIG(status) == 2)
			write(2, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
