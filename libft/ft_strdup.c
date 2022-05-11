/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 08:59:07 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/01 14:16:30 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	dest = (char *)malloc(ft_strlen(src) + 1);
	if (dest != NULL)
	{
		while (*(src + i))
		{
			*(dest + i) = *(src + i);
			i++;
		}
		*(dest + i) = '\0';
		return (dest);
	}
	return (NULL);
}
