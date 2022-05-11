/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:51:48 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/06 17:31:20 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_ast_node(t_tok tok)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	gc_add_back(new_gcnode((void *)cmd));
	if (!cmd)
		return (NULL);
	if (tok & BG)
		cmd -> type = AST_BG;
	else if (tok & SC)
		cmd -> type = AST_SC;
	else if (tok & PP)
		cmd -> type = AST_PIPE;
	else if ((tok & OR) & OR)
		cmd -> type = AST_OR;
	else if ((tok & AND) & AND)
		cmd -> type = AST_AND;
	else if (tok & OPR)
		cmd -> type = AST_SUB;
	return (cmd);
}

void	new_exec_node_util(t_cmd *cmd, t_token *first, int *ac)
{
	while (!(first -> tok & CMDEND))
	{
		if (first -> tok & REDIR && first -> next -> next)
		{
			first = first -> next -> next;
			continue ;
		}
		if (first -> tok & WC && first -> group)
		{
			while ((*first -> group) && (*first -> group)-> data)
			{
				cmd -> argv[*ac] = (*first -> group)-> data;
				*ac += 1;
				(*first -> group) = (*first -> group)-> next;
			}
		}
		else if (first -> tok & STR)
		{
			cmd -> argv[*ac] = first -> data;
			*ac += 1;
		}
		first = first -> next;
	}
	cmd -> argv[*ac] = 0;
}

t_cmd	*new_exec_node(t_cmd *cmd, t_token **tokens)
{
	t_token	*first;
	int		ac;

	ac = 0;
	first = *tokens;
	cmd = malloc(sizeof(t_cmd));
	gc_add_back(new_gcnode((void *)cmd));
	if (!cmd)
		return (NULL);
	cmd -> type = AST_EXEC;
	new_exec_node_util(cmd, first, &ac);
	return (cmd);
}

static void	fill_redir(t_cmd **cmd, t_tok tok)
{
	(*cmd)->fd = 0;
	if (tok & GTH)
	{
		(*cmd)->fd = 1;
		(*cmd)-> mode = O_CREAT | O_WRONLY | O_TRUNC;
	}
	else if (tok & GGTH)
	{
		(*cmd)-> mode = O_CREAT | O_WRONLY | O_APPEND;
		(*cmd)->fd = 1;
	}
	else if (tok & LTH)
		(*cmd)->fd = 0;
	else if (tok & HDOC)
		(*cmd)->fd = 0;
}

t_cmd	*new_redir_node(t_cmd *cmd1, t_token **toks, t_tok tok)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	gc_add_back(new_gcnode((void *)cmd));
	if (!cmd)
		return (cmd1);
	cmd -> mode = O_RDONLY;
	if (tok & GTH)
		cmd -> type = AST_GTH;
	else if (tok & GGTH)
		cmd -> type = AST_GGTH;
	else if (tok & LTH)
		cmd -> type = AST_LTH;
	else if (tok & HDOC)
		cmd -> type = AST_HDOC;
	fill_redir(&cmd, tok);
	cmd -> file = (*toks)-> next -> data;
	cmd -> right = cmd1;
	return (cmd);
}
