/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:30 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 16:46:25 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_m
{
	char		*key;
	char		*cokey;
	char		*path;
	int			len;
	int			i;
	char		**env;
	char		*val;
	char		*v;
	int			shlvl;
}	t_m;

void	pwd_cmd(void);
char	*get_path(char *cmd);
void	echo_cmd(char **cmd);
void	cd_cmd(char **args);
void	export_cmd(char **args);
void	env_cmd(char **args);
void	exit_num(char **args);
void	exit_cmd(char **args);
void	unset_cmd(char **args);
void	del_venv(char *key);
void	show_vars(void);
void	print_error_(char *f, char *m, char *l);
int		if_egal(char *arg);
int		if_plusegal(char *arg);
void	print_quotes(void);
void	export_print(t_venv **ve);
void	sort_env( t_venv **venv);
void	env_go(char *arg);
int		runcmd(t_cmd *cmd);
int		ft_execve(char **cmd);
void	run_exec(t_cmd *cmd);
int		run_redir(t_cmd	*cmd);
int		run_and(t_cmd	*cmd);
int		run_or(t_cmd	*cmd);
int		run_back(t_cmd	*cmd);
int		run_sub(t_cmd	*cmd);
int		run_hdoc(char *delim);
void	run_hdoc_util(t_cmd *cmd);
pid_t	run_pipe_util(t_cmd *cmd, int fd[2], int s);
int		get_status(int status);
void	close_pipe(int fds[2]);
pid_t	ft_fork(void);
int		ft_pipe(int fildes[2]);
void	reset_io(int io[2]);
void	save_io(int io[2]);

#endif