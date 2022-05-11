/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:32:11 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/07 23:02:52 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

t_tok	redir_tok(t_token *token)
{
	t_tok	tok;

	tok = 0;
	if ((token -> tok & GTH) & GTH)
		tok = GTH;
	else if ((token ->tok & GGTH) & GGTH)
		tok = GGTH;
	else if ((token ->tok & LTH) & LTH)
		tok = LTH;
	else if ((token ->tok & HDOC) & HDOC)
		tok = HDOC;
	return (tok);
}

t_cmd	*parseredir(t_cmd *cmd, t_token **tokens)
{	
	t_cmd	*cmd1;
	t_tok	token;

	if ((*tokens)->tok & CMDEND)
		return (cmd);
	cmd1 = cmd;
	if ((*tokens)-> tok & REDIR)
	{
		token = redir_tok(*tokens);
		cmd1 = new_redir_node(cmd, tokens, token);
		if (!cmd1)
			return (cmd);
	}
	return (cmd1);
}

t_cmd	*parsecmd(t_token **tokens)
{
	t_cmd	*cmd;
	t_token	*first;
	t_token	*tmp;
	t_cmd	*cmd1;

	cmd = NULL;
	if (!*tokens)
		return (NULL);
	first = *tokens;
	tmp = *tokens;
	cmd = new_exec_node(cmd, tokens);
	while (!(first -> tok & CMDEND))
		first = first -> next;
	while (first != tmp)
	{
		cmd = parseredir(cmd, &first);
		first = first -> prev;
	}
	cmd = parseredir(cmd, &first);
	cmd1 = cmd;
	parsehdoc(cmd);
	return (cmd1);
}

t_cmd	*parseline(t_token **tokens)
{
	t_cmd	*cmd;

	if (is_there(tokens, SC | BG, 0))
		cmd = parselist(tokens);
	else if (is_there(tokens, AND, 0))
		cmd = parsecondition(tokens, AND);
	else if (is_there(tokens, OR, 0))
		cmd = parsecondition(tokens, OR);
	else if (is_there(tokens, PP, 0))
		cmd = parsepipe(tokens);
	else if (is_there(tokens, OPR, 1))
		cmd = parseblock(tokens);
	else
		cmd = parsecmd(tokens);
	return (cmd);
}

t_cmd	**parsing(t_token **tokens)
{
	t_cmd	**cmd;
	t_token	*tok;

	if (!tokens || !*tokens)
		return (NULL);
	cmd = malloc(sizeof(t_cmd *));
	gc_add_back(new_gcnode((void *)cmd));
	if (!cmd)
		return (NULL);
	tok = *tokens;
	if (!tok || !tokens)
		return (NULL);
	*cmd = parseline(tokens);
	return (cmd);
}
