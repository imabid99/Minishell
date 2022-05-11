/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:01:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/02 23:26:49 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	i = 0;
	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	if (!s11 && !s22)
		return (0);
	if (!s11 || !s22)
		return (1);
	if (n > 0)
	{
		while (*s11 && *s22 && (*s11 == *s22) && i < n - 1)
		{
			i++;
			s11++;
			s22++;
		}
		return (*s11 - *s22);
	}
	return (0);
}
