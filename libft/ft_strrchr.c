/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:30:40 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/18 17:34:50 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*a;

	a = s + ft_strlen(s);
	while (a != s - 1)
	{
		if (*a == (char)c)
			return ((char *)a);
		a--;
	}
	return (NULL);
}
