/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:59:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/18 17:34:58 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	char			*t;
	size_t			lenght;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	lenght = ft_strlen(s + start);
	if (lenght >= len)
		lenght = len;
	sub = (char *)malloc(lenght + 1);
	t = sub;
	if (!sub)
		return (NULL);
	while (*(s + start) && lenght-- > 0)
	{
		*sub = *(s + start);
		s++;
		sub++;
	}
	*sub = '\0';
	return (t);
}
