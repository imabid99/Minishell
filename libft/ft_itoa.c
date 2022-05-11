/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:17:10 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/18 17:33:26 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(int n)
{
	int	i;

	i = 1;
	n /= 10;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

void	is_neg(long *n, int *len)
{
	if (*n < 0)
	{
		*n *= -1;
		*len += 1;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	long	nb;
	int		len;

	nb = n;
	len = get_len(nb);
	is_neg(&nb, &len);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	*(s + len) = '\0';
	if (nb == 0)
		*(s + 0) = '0';
	while (nb)
	{
		*(s + len - 1) = nb % 10 + 48;
		nb = nb / 10;
		len--;
	}
	if (n < 0)
		*s = '-';
	return (s);
}
