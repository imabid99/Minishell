/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:17:12 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/03 13:19:56 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dquot_util(char **line, t_token **tok)
{
	add_token_back(tok, new_token(STR, ft_strdup("")));
	add_token_back(tok, new_token(DQT, ft_strdup("\"")));
	*line += 2;
}

int	tok_3_util(char **s, char **line, t_token **tok)
{
	add_token_back(tok, new_token(DQT, ft_strdup("\"")));
	if (*(*s + 1) == '\"')
	{
		dquot_util(line, tok);
		return (1);
	}
	*s += 1;
	return (0);
}

void	dquote_util_1(char **s, t_token **tok)
{
	if (**s == '\"')
	{
		add_token_back(tok, new_token(DQT, ft_strdup("\"")));
		*s += 1;
	}
}

char	*dollar_util(int *len, char **line, t_token **tok, char **s)
{
	if (*len > 1)
		add_token_back(tok, new_token(STR, ft_strndup(*line, *len)));
	*line = tokenize_4(s, tok, 0);
	*s = *line;
	*len = 1;
	return (*s);
}

void	tokenize_3(char **line, t_token **tok, int len)
{
	char	*s;

	s = *line;
	if (tok_3_util(&s, line, tok))
		return ;
	*line += 1;
	s = *line;
	while (*s && *s != '\n' && *s != '\"')
	{
		if (*s == '$')
			s = dollar_util(&len, line, tok, &s);
		else
		{
			len++;
			s++;
		}
	}
	if (len > 1)
		add_token_back(tok, new_token(STR, ft_strndup(*line, len)));
	dquote_util_1(&s, tok);
	*line = s;
}
