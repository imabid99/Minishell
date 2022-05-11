/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 16:29:33 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_0(char **line, t_token **tok)
{
	char	*s;

	s = *line;
	while (*s && ft_strchr(SPACES, *s))
		s++;
	if (*s != **line)
		add_token_back(tok, new_token(WSC, ft_strdup("")));
	*line = s;
}

void	tokenize_2(char **line, t_token **tok)
{
	int		len;
	char	*s;

	s = *line + 1;
	len = 0;
	add_token_back(tok, new_token(QT, ft_strdup("\'")));
	while (*s && *s != '\n' && *s != '\'')
	{
		len++;
		s++;
	}
	add_token_back(tok, new_token(STR, ft_strndup(*line + 1, len + 1)));
	if (*s == '\'')
	{
		add_token_back(tok, new_token(QT, ft_strdup("\'")));
		s++;
	}
	*line = s;
}

char	*tokenize_4(char **line, t_token **tok, int q)
{
	int		len;
	char	*s;

	len = 0;
	s = *line + 1;
	if (*s == '$' || *s == '?' || ft_isdigit(*s))
	{
		add_token_back(tok, new_token(VAR, ft_strndup(*line + 1, 2)));
		return (*line + 2 - q);
	}
	while (*s && (ft_isalnum(*s) || *s == '_') && *s != '\"')
	{
		len++;
		s++;
	}
	if (len)
		add_token_back(tok, new_token(VAR, ft_strndup(*line + 1, len + 1)));
	else
		add_token_back(tok, new_token(STR, ft_strndup(*line, 2)));
	*line = s;
	return (*line);
}

void	tokenize_5(char **line, t_token **tok)
{
	char	*s;
	char	*copy;
	int		len;

	s = *line;
	len = 0;
	while (*s && !ft_strchr("<>()|;\'\"$& ", *s))
	{
		s++;
		len++;
	}
	copy = ft_strndup(*line, len + 1);
	gc_add_back(new_gcnode((void *)copy));
	if (copy[0] == '~' && (copy[1] == '/' || !copy[1]))
	{
		add_token_back(tok, new_token(TLD,
				ft_strndup(copy, 1 + (copy[1] == '/'))));
		*line += 1;
		return ;
	}
	else if (ft_strchr(copy, '*') || ft_strchr(copy, '?'))
		add_token_back(tok, new_token(WC, ft_strdup(copy)));
	else
		add_token_back(tok, new_token(STR, ft_strdup(copy)));
	*line = s;
}

t_token	**tokenizer(char **line, char *charset)
{
	t_token	**token;

	token = NULL;
	token = token_init(token);
	*token = new_token(CMDBEG, ft_strdup(""));
	while (**line && **line != '#')
	{
		if (peek(line, SPACES))
			tokenize_0(line, token);
		else if (**line == '\'')
			tokenize_2(line, token);
		else if (**line == '"')
			tokenize_3(line, token, 1);
		else if (peek(line, "$"))
			*line = tokenize_4(line, token, 0);
		else if (peek(line, charset))
			tokenize_1(line, token);
		else
			tokenize_5(line, token);
	}
	return (token);
}
