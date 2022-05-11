/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:00:28 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/18 17:34:17 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char sep, char c)
{
	if (sep == '\0')
		return (1);
	else if (c == sep)
		return (1);
	return (0);
}

int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (!is_sep(s[i], c) && \
				(is_sep(s[i + 1], c) || s[i + 1] == '\0' ))
			words++;
		i++;
	}
	return (words);
}

void	ft_copy_word(char *dest, char const *from, char c)
{
	int	i;

	i = 0;
	while (!is_sep(from[i], c))
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

int	ft_move_to_tab(char **tab, char const *s, char c)
{
	int	i;
	int	j;
	int	word;

	word = 0;
	i = 0;
	while (s[i])
	{
		if (is_sep(s[i], c))
			i++;
		else
		{
			j = 0;
			while (!is_sep(s[i + j], c))
				j++;
			tab[word] = (char *)malloc(j + 1);
			if (!tab)
				return (0);
			ft_copy_word(tab[word], s + i, c);
			i = i + j;
			word++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		word;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	word = count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (!tab)
		return (NULL);
	tab[word] = 0;
	if (!ft_move_to_tab(tab, s, c))
	{
		while (tab[i++])
		{
			free(tab[i]);
		}
		free(tab);
	}
	return (tab);
}
