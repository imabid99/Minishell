/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:00:52 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/06 14:06:48 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	int		len_tot;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	len_tot = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = (char *)malloc(len_tot * sizeof(char));
	if (!s)
		return (NULL);
	while (*s1)
		*s++ = *s1++;
	while (*s2)
		*s++ = *s2++;
	*s = '\0';
	return (s - len_tot + 1);
}
