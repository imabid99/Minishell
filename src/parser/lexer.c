/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 02:24:10 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/07 16:21:35 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	**filter_wc(t_token **toks)
{
	t_token	*first;

	first = *toks;
	while (first)
	{
		if (first -> tok & WC)
		{
			if (!first ->group || !*first -> group || !(*first -> group)-> data)
				first -> tok = STR;
		}
		first = first -> next;
	}
	return (toks);
}

static t_token	**del_wspaces(t_token **tokens)
{
	t_token	*first;

	first = *tokens;
	while (first -> next)
	{
		if ((first -> tok & WSC) && first -> next -> tok & (BIND | BFG))
			del_token_0(first);
		first = first -> next;
	}
	return (tokens);
}

t_token	**lexer(char **line, char **env)
{
	t_token	**tokens;

	(void)env;
	if (!line || !*line || !**line)
		return (NULL);
	if (**line)
		add_history(*line);
	tokens = tokenizer(line, "<>&;()|");
	tokens = del_wspaces(tokens);
	if (!tokens)
		return (NULL);
	add_token_back(tokens, new_token(CMDEND, ft_strdup("newline")));
	if (syntax_analyse(tokens))
	{
		g_glob.status = 2;
		return (NULL);
	}
	g_glob.vars = set_global_vars(g_glob.vars);
	tokens = quotes_filter(tokens);
	tokens = concat_words(tokens);
	tokens = expander(tokens);
	tokens = filter_wc(tokens);
	tokens = concat_words(tokens);
	return (tokens);
}
