/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:25:54 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 16:42:14 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_error(char *s)
{
	if (!s)
	{
		write(2, "invalid command!\n", 18);
		return (1);
	}
	else
	{
		print_error_("minishell: ", s, ": Command not found\n");
		return (1);
	}
	return (1);
}

char	*get_path(char *cmd)
{
	t_m	m;
	DIR	*directory;

	directory = opendir(cmd);
	m.val = get_venv("PATH", g_glob.venv);
	m.i = 0;
	if (access(cmd, X_OK) == 0 && !directory)
		return (cmd);
	if (directory)
		closedir(directory);
	m.path = ft_strtok(m.val, ':');
	gc_add_back(new_gcnode((void *)m.path));
	while (m.path)
	{
		m.path = ft_strjoin(m.path, "/");
		gc_add_back(new_gcnode((void *)m.path));
		m.path = ft_strjoin(m.path, cmd);
		gc_add_back(new_gcnode((void *)m.path));
		if (access(m.path, X_OK) == 0)
			return (m.path);
		m.path = ft_strtok(NULL, ':');
		m.i++;
	}
	get_error(cmd);
	return (0);
}

int	get_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			write(2, "Quit: 3\n", 8);
		if (WTERMSIG(status) == 2)
			write(2, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	else if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (print_error("fork", strerror(errno)), -1);
	return (pid);
}
