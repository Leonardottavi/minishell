/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:53:47 by lottavi           #+#    #+#             */
/*   Updated: 2023/04/14 11:53:48 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = dst;
	s = src;
	if (!dst && !src)
		return (dst);
	if (src < dst)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i++ < len)
			d[i - 1] = s[i - 1];
	}
	return (dst);
}
