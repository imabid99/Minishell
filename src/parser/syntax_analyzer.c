/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:59:44 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/29 16:39:07 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unexpected(t_token **tokens)
{
	t_token	*first;

	first = *tokens;
	while (first)
	{
		if (first -> tok == DSC)
			return (print_error(UNEXPECTED_TOK, ";;"), 1);
		first = first -> next;
	}
	return (0);
}

int	syntax_analyse(t_token **tokens)
{
	if (check_par_match(tokens)
		|| check_quotes_match(tokens) || check_binders(tokens)
		|| check_redirect(tokens) || check_parethesis(tokens)
		|| check_unexpected(tokens))
		return (1);
	return (0);
}
