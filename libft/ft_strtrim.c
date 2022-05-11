/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 09:57:43 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/18 17:34:55 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	long	first;
	long	last;
	char	*s;

	first = 0;
	if (!s1 || !set)
		return (NULL);
	last = ft_strlen(s1) - 1;
	while (is_set(*(s1 + first), set))
		first++;
	while (is_set(*(s1 + last), set) && last >= 0)
		last--;
	if (last < 0)
		return (ft_strdup(""));
	s = malloc(last - first + 2);
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1 + first, last - first + 2);
	return (s);
}
