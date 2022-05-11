/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:14 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/08 01:45:15 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin(char *cmd, char **argv)
{
	if (!ft_strncmp(cmd, "echo", sizeof("echo") + 1))
		return (echo_cmd(argv), true);
	else if (!ft_strncmp(cmd, "cd", sizeof("cd") + 1))
		return (cd_cmd(argv), true);
	else if (!ft_strncmp(cmd, "pwd", sizeof("pwd") + 1))
		return (pwd_cmd(), true);
	else if (!ft_strncmp(cmd, "export", sizeof("export") + 1))
		return (export_cmd(argv), true);
	else if (!ft_strncmp(cmd, "unset", sizeof("unset") + 1))
		return (unset_cmd(argv), true);
	else if (!ft_strncmp(cmd, "env", sizeof("env") + 1))
		return (env_cmd(argv), true);
	else if (!ft_strncmp(cmd, "exit", sizeof("exit") + 1))
		return (exit_cmd(argv), true);
	return (false);
}

void	run_exec(t_cmd *cmd)
{
	int	ret;

	if (is_builtin(cmd ->argv[0], cmd ->argv))
		return ;
	if (!cmd ->argv[0])
		return ;
	ret = ft_execve(cmd -> argv);
	if (ret == 127)
		g_glob.status = 127;
	if (ret == -2)
		return ;
}

void	run_list(t_cmd *cmd)
{
	runcmd(cmd->left);
	if (cmd ->right && (cmd->right->argv[0] || cmd->right->type & AST_NOD))
		runcmd(cmd->right);
}

void	run_pipe(t_cmd *cmd)
{
	int	status[2];
	int	pid[2];
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	pid[0] = run_pipe_util(cmd, fd, 1);
	if (pid[0] == -1)
		return ;
	pid[1] = run_pipe_util(cmd, fd, 2);
	if (pid[1] == -1)
		return ;
	close_pipe(fd);
	waitpid(pid[0], &status[0], WUNTRACED);
	waitpid(pid[1], &status[1], WUNTRACED);
	g_glob.status = get_status(status[1]);
}

int	runcmd(t_cmd *cmd)
{
	t_cmd	*root;

	if (!cmd)
		return (1);
	root = cmd;
	if (root ->type & AST_AND)
		run_and(root);
	else if (root ->type & AST_OR)
		run_or(root);
	else if (root ->type & AST_BG)
		run_back(root);
	else if (root ->type & AST_EXEC)
		run_exec(root);
	else if (root ->type & AST_SC)
		run_list(root);
	else if (root -> type & AST_REDIR)
		run_redir(root);
	else if (root ->type & AST_PIPE)
		run_pipe(root);
	else if (root ->type & AST_SUB)
		run_sub(root);
	return (0);
}
