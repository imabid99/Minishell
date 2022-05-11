/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:29:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/18 17:34:00 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst1;
	const char	*src1;

	if (!src && !dst)
		return (NULL);
	dst1 = dst;
	src1 = src;
	if (src1 < dst1)
	{
		dst1 += len - 1;
		src1 += len - 1;
		while (0 < len--)
			*dst1-- = *src1--;
	}
	else
		ft_memcpy(dst1, src1, len);
	return (dst);
}
