/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:28:27 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 01:19:01 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_add(t_m *m)
{
	m->shlvl = ft_atoi(get_venv("SHLVL", g_glob.venv));
	m->shlvl++;
	add_global_venv(ft_strdup("SHLVL"), ft_itoa(m->shlvl), g_glob.venv);
	add_global_venv(ft_strdup("SHLVL"), ft_itoa(m->shlvl), g_glob.ennv);
}

void	lets_start(char **env)
{
	g_glob.venv = set_global_env(env, g_glob.venv);
	g_glob.ennv = set_global_env(env, g_glob.ennv);
}

void	init_minishell(char **env)
{
	t_m		m;

	g_glob.gc = init_gc();
	rl_catch_signals = 0;
	lets_start(env);
	shlvl_add(&m);
	signal_handl();
	save_io(g_glob.io);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	**cmd;
	t_token	**toks;

	(void)av;
	(void)ac;
	init_minishell(env);
	while (1)
	{
		g_glob.g = 0;
		line = readline("minishell$ ");
		gc_add_back(new_gcnode((void *)line));
		if (!line)
			ctrl_d();
		toks = lexer(&line, env);
		if (toks)
		{
			cmd = parsing(toks);
			g_glob.g = 1;
			runcmd(*cmd);
		}
		reset_io(g_glob.io);
	}
	return (0);
}
