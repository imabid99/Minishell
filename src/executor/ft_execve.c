/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:33:18 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/08 01:37:42 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	venv_count(t_venv *venv)
{
	int	counter;

	counter = 0;
	while (venv)
	{
		counter++;
		venv = venv->next;
	}
	return (counter);
}

char	**venv_export_array(t_venv	*venv)
{
	t_m	m;

	m.i = 0;
	m.len = venv_count(venv);
	m.env = malloc(sizeof(char *) * (m.len + 1));
	gc_add_back(new_gcnode((void *)m.env));
	while (venv && m.i < m.len)
	{
		m.path = ft_strjoin(venv->key, "=");
		gc_add_back(new_gcnode((void *)m.path));
		m.path = ft_strjoin(m.path, venv->value);
		m.env[m.len - m.i++ - 1] = m.path;
		gc_add_back(new_gcnode((void *)m.path));
		venv = venv->next;
	}
	m.env[m.len] = NULL;
	return (m.env);
}

int	ft_execve(char **cmd)
{
	char	*path;
	char	**env;
	int		pid;
	int		status;

	path = get_path(*cmd);
	if (!path)
		return (127);
	env = venv_export_array(*g_glob.venv);
	pid = fork();
	if (pid == -1)
		return (-2);
	else if (pid == 0)
	{
		execve(path, cmd, env);
		if (errno == ENOENT)
			exit(127);
		if (errno == EACCES)
			exit(126);
	}
	waitpid(pid, &status, WUNTRACED);
	g_glob.status = get_status(status);
	return (g_glob.status);
}
