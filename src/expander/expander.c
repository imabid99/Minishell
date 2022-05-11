/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:31:39 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 13:00:48 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	char_matching(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '\0')
		return (true);
	if (*s1 == '?' && *s2 == '\0')
		return (false);
	if (s1 + 1)
	{
		if ((*s1 == '*' || *s1 == '?') && *(s1 + 1) != '\0' && *s2 == '\0')
			return (false);
	}
	if (*s1 == '?' || *s1 == *s2)
		return (char_matching(s1 + 1, s2 + 1));
	if (*s1 == '*')
		return (char_matching(s1 + 1, s2) || char_matching(s1, s2 + 1));
	return (false);
}

t_group	**expand_group(t_token *token)
{
	struct dirent	*de;
	DIR				*dr;
	char			*s;

	token -> group = init_group();
	dr = opendir("./");
	if (dr == NULL || !token -> group)
		return (NULL);
	if (*token->data == '.' && *(token -> data + 1) == '/')
		token->data += 2;
	de = readdir(dr);
	while (de != NULL)
	{
		s = ft_strdup(de -> d_name);
		if (ft_strcmp(s, ".") && ft_strcmp(s, "..") && s[0] != '.')
		{
			if (char_matching(token -> data, s) == true)
				gnode_add_back(token -> group, new_gnode(s));
		}
		de = readdir(dr);
		gc_add_back(new_gcnode((void *)s));
	}
	closedir(dr);
	return (token -> group);
}

static t_token	**expand_wildcard(t_token **tokens)
{
	t_token	*first;

	first = *tokens;
	while (first)
	{
		if (first -> tok & WC && !((first -> prev -> tok) & NO_EXP))
		{
			first -> tok = STR;
			first = first -> next;
		}
		if (first -> tok & WC)
		{
			first -> group = expand_group(first);
		}
		first = first -> next;
	}
	return (tokens);
}

static t_token	**expand_dollar(t_token **tokens)
{
	t_token	*first;
	char	*data;

	first = *tokens;
	while (first)
	{
		if (first -> tok & VAR)
		{
			data = get_venv_all(first -> data);
			first -> data = ft_strdup(data);
			gc_add_back(new_gcnode((void *)first -> data));
			first -> tok = STR;
		}
		else if (first -> tok & TLD)
		{
			first -> data = ft_strdup(get_venv("HOME", g_glob.venv));
			gc_add_back(new_gcnode((void *)first -> data));
			first -> tok = STR;
		}
		if (!first -> data)
			del_token_0(first);
		first = first -> next;
	}
	return (tokens);
}

t_token	**expander(t_token **tokens)
{
	tokens = expand_dollar(tokens);
	tokens = expand_wildcard(tokens);
	return (tokens);
}
