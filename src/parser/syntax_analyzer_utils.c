/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:36:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 12:47:48 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_par_match(t_token **tokens)
{
	t_token	*first;
	int		pcount;

	first = *tokens;
	pcount = 0;
	while (first)
	{
		if (first->tok == OPR)
			pcount++;
		if (first->tok == CPR)
			pcount--;
		first = first -> next;
	}
	if (pcount)
		return (print_error(UNCLOSED_PAR, "\0"), 1);
	return (0);
}

int	check_quotes_match(t_token **tokens)
{
	t_tok_util	t;

	t.first = *tokens;
	t.count[0] = 0;
	t.count[1] = 0;
	while (t.first -> next)
	{
		if (t.first->tok == DQT)
			t.count[1] += 1;
		if (t.first->tok == QT)
			t.count[0] += 1;
		t.first = t.first -> next;
	}
	t.first = *tokens;
	while (t.first && (t.first -> tok != DQT) && (t.first -> tok != QT))
		t.first = t.first -> next;
	if (t.count[1] % 2 && t.first -> tok == DQT)
		return (print_error(UNCLOSED_DQ, "\0"), 1);
	else if (t.count[0] % 2 && t.first -> tok == QT)
		return (print_error(UNCLOSED_SQ, "\0"), 1);
	else if (t.count[1] % 2)
		return (print_error(UNCLOSED_DQ, "\0"), 1);
	else if (t.count[0] % 2)
		return (print_error(UNCLOSED_SQ, "\0"), 1);
	return (0);
}

int	check_parethesis(t_token **tokens)
{
	t_tok_util	t;

	t.first = *tokens;
	while (t.first -> next -> next)
	{
		t.right = t.first -> next;
		t.left = t.first -> prev;
		if (t.first -> tok == CPR)
		{
			if (!(t.left -> tok & (WORD | CPR)))
				return (print_error(UNEXPECTED_TOK, t.left -> data), 1);
			else if (!(t.right -> tok & (CPR | BIND | BFG | CMDEND | REDIR)))
				return (print_error(UNEXPECTED_TOK, t.right -> data), 1);
		}
		if (t.first -> tok == OPR)
		{
			if (!(t.left -> tok & (OPR | CMDBEG | BIND | BFG | WSC)))
				return (print_error(UNEXPECTED_TOK, "("), 1);
			else if (!(t.right -> tok & (WORD | REDIR | OPR)))
				return (print_error(UNEXPECTED_TOK, t.right -> data), 1);
		}
		t.first = t.first -> next;
	}
	return (0);
}

int	check_binders(t_token **tokens)
{
	t_tok_util	t;

	t.first = *tokens;
	while (t.first -> next)
	{
		t.right = t.first -> next;
		t.left = t.first -> prev;
		if (t.first -> tok & BIND)
		{
			if (!(t.left -> tok & (WORD | CPR)))
				return (print_error(UNEXPECTED_TOK, t.first -> data), 1);
			if (!(t.right -> tok & (WORD | REDIR | OPR)))
				return (print_error(UNEXPECTED_TOK, t.right -> data), 1);
		}
		if (t.first -> tok & BFG)
		{
			if (!(t.left -> tok & (WORD | CPR)))
				return (print_error(UNEXPECTED_TOK, t.first -> data), 1);
			if (!(t.right -> tok & (WORD | REDIR | OPR | CMDEND)))
				return (print_error(UNEXPECTED_TOK, t.right -> data), 1);
		}
		t.first = t.first -> next;
	}
	return (0);
}

int	check_redirect(t_token **tokens)
{
	t_token	*first;
	t_token	*right;

	first = *tokens;
	while (first -> next)
	{
		right = first -> next;
		if ((first -> tok & REDIR))
		{
			if (!(right -> tok & WORD))
				return (print_error(UNEXPECTED_TOK, right -> data), 1);
		}
		first = first -> next;
	}
	return (0);
}
