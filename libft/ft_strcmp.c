/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:27:36 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/27 04:31:19 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	if (!s11 && !s22)
		return (0);
	if (!s11 || !s22)
		return (1);
	while (*s11 && *s22 && (*s11 == *s22))
	{
		s11++;
		s22++;
	}
	return (*s11 - *s22);
}
