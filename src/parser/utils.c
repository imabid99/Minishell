/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:02:51 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/08 00:10:03 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str, char *data)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(data, 2);
	ft_putchar_fd('\n', 2);
}

int	peek(char **line, char *toks)
{
	char	*s;

	s = *line;
	return (*s && ft_strchr(toks, *s));
}

void	save_io(int io[2])
{
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
	if (io[0] == -1 || io[1] == -1)
		print_error("dup", strerror(errno));
}

void	reset_io(int io[2])
{
	if (dup2(io[0], STDIN_FILENO) == -1 || dup2(io[1], STDOUT_FILENO) == -1)
		print_error("dup2", strerror(errno));
}
