/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:20:15 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 01:18:08 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*escape_block(t_token *first)
{
	int		count;
	t_token	*save;

	save = first;
	count = 0;
	while (save && save -> tok != CMDEND)
	{
		if (save -> tok & OPR)
			count++;
		if (save -> tok & CPR)
			count--;
		save = save -> next;
		if (!count)
			break ;
	}
	first = save;
	return (first);
}

static void	del_parethesis(t_token **tokens)
{
	t_token	*first;

	first = *tokens;
	if (!first -> next)
		return ;
	while (first -> next -> tok != CMDEND)
		first = first -> next;
	if (first && first -> tok == CPR)
		del_token_0(first);
}

t_split	find(t_token **tokens, t_tok tok, int isbloc)
{
	t_token	*first;
	t_split	sp;

	first = *tokens;
	sp.right = NULL;
	sp.left = NULL;
	sp.right = token_init(sp.right);
	sp.left = token_init(sp.left);
	while (first && first -> tok != CMDEND)
	{
		if (first -> tok & OPR && !isbloc)
			first = escape_block(first);
		if (first -> tok & tok)
			break ;
		first = first -> next;
	}
	sp.tok = first -> tok;
	*(sp.right) = first -> next;
	if (isbloc && *sp.right)
		del_parethesis(sp.right);
	first -> tok = CMDEND;
	*(sp.left) = *tokens;
	return (sp);
}

int	is_there(t_token **tokens, t_tok tok, int isbloc)
{
	t_token	*first;
	int		ret;

	ret = 0;
	if (!*tokens)
		return (0);
	first = *tokens;
	while (first && first -> tok != CMDEND)
	{
		if (first -> tok & OPR && !isbloc)
			first = escape_block(first);
		if (first -> tok & tok)
		{
			ret = 1;
			break ;
		}
		first = first -> next;
	}
	return (ret);
}
