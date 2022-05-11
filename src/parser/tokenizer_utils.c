/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 02:51:48 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/02 23:08:26 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok1_util(t_tokenizer *t, char *val, t_token **tok)
{
	if (t -> tok1 & (PP | GTH | LTH | BG | SC))
	{
		if (t -> tok2 && *(t -> s) == *(t -> s - 1))
		{
			val[0] = *(t -> s - 1);
			val[1] = *(t -> s - 1);
			val[2] = 0;
			add_token_back(tok, new_token(t -> tok2, ft_strdup(val)));
			(t -> s)++;
		}
		else
		{
			val[0] = *((t -> s - 1));
			val[1] = 0;
			add_token_back(tok, new_token(t -> tok1, ft_strdup(val)));
		}
	}
}

void	tokenize_1(char **line, t_token **tok)
{
	char		val[3];
	t_tokenizer	t;

	(t.s) = *line;
	t.tok1 = (*t.s == '|') * PP + (*t.s == '>') * GTH + (*t.s == '<') * LTH \
		+ (*t.s == '&') * BG + (*t.s == '(') * OPR + (*t.s == ')') * CPR \
		+ (*t.s == ';') * SC;
	(t.s)++;
	t.tok2 = (*t.s == '|') * OR + (*t.s == '>') * GGTH + (*t.s == '<') * HDOC \
		+ (*t.s == '&') * AND + (*t.s == ';') * DSC;
	if (t.tok1 & (OPR | CPR | QT | DQT))
	{		
		val[0] = *((t.s - 1));
		val[1] = 0;
		add_token_back(tok, new_token(t.tok1, ft_strdup(val)));
	}
	tok1_util(&t, val, tok);
	while (*t.s && ft_strchr(SPACES, *t.s))
		t.s++;
	*line = (t.s);
}

/***
void	bslash_util(int *len, char **line, t_token **tok, char **s)
{
	if (*len > 1)
		add_token_back(tok, new_token(STR, ft_strndup(*line + 1, *len)));
	*line = tokenize_6(s, tok);
	*s = *line;
	*len = 1;
}

char	*tokenize_6(char **line, t_token **tok)
{
	char	*s;
	char	*copy;
	int		len;

	*line += 1;
	s = *line;
	if (!s || !*s)
		return (0);
	len = 1;
	copy = ft_strdup(*line);
	copy[len] = '\0';
	add_token_back(tok, new_token(STR, ft_strdup(copy)));
	*line = s + 1;
	free(copy);
	return (*line);
}
*/