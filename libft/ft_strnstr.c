/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:13:40 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/18 17:34:47 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && i < len)
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j) && i + j < len)
		{
			if (*(needle + j + 1) == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (0);
}
