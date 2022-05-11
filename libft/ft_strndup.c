/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 00:18:32 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/27 04:30:59 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int len)
{
	char	*copy;

	copy = (char *)malloc(len * sizeof(char));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s, len);
	return (copy);
}
