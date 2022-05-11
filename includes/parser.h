/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 17:27:00 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "ast.h"
# include "tokenizer.h"
# define ARG_MAX 262144

typedef struct s_cmd
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
	char			*argv[ARG_MAX];
	char			*file;
	int				mode;
	int				fd;
	int				out;
}	t_cmd;

t_split	find(t_token **tokens, t_tok tok, int isbloc);
int		is_there(t_token **tokens, t_tok tok, int isbloc);
t_cmd	**parsing(t_token **tokens);
t_cmd	*parseline(t_token **tokens);
t_cmd	*parselist(t_token **tokens);
t_cmd	*parsecmd(t_token **tokens);
t_cmd	*parseredir(t_cmd *cmd, t_token **tokens);
t_cmd	*parsecondition(t_token **tokens, t_tok tok);
t_cmd	*parsepipe(t_token **tokens);
t_cmd	*parseblock(t_token **tokens);
t_cmd	*parseback(t_token **tokens);
void	parsehdoc(t_cmd *cmd);
t_cmd	*new_exec_node(t_cmd *cmd, t_token **tokens);
t_cmd	*new_ast_node(t_tok tok);
t_cmd	*new_redir_node(t_cmd *cmd1, t_token **toks, t_tok tok);

#endif
