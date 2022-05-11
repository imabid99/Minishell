/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 16:53:49 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "gc.h"

typedef struct s_venv
{
	char			*key;
	char			*value;
	struct s_venv	*next;
}	t_venv;

typedef struct s_glob
{
	t_venv	**venv;
	t_venv	**ennv;
	t_venv	**vars;
	t_venv	**buff;
	int		status;
	int		io[2];
	t_gc	**gc;
	int		g;
}	t_glob;

t_venv	**set_global_env(char **env, t_venv **ennv);
t_venv	**set_global_vars(t_venv **vars);
void	add_global_venv(char *key, char *value, t_venv **all);
void	del_venv(char *key);
char	*get_venv(char *key, t_venv **all);
char	*get_venv_all(char *key);
char	*get_var(char *key);
char	*get_key(char *env);
void	show_vars(void);
char	*get_value(char *env);
t_venv	**init_venv(t_venv **venv);
t_venv	*new_venv(char *key, char *value);
void	venv_add_back(t_venv **venv, t_venv *new);
t_group	**init_group(void);
t_group	*new_gnode(char *data);
void	gnode_add_back(t_group **group, t_group *new);
void	del_ennv(char *key);
t_token	**expander(t_token **tokens);

#endif
