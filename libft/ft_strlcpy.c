/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:55:12 by lottavi           #+#    #+#             */
/*   Updated: 2023/04/14 11:55:14 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	cpysize;

	if (dstsize > ft_strlen(src))
		cpysize = ft_strlen(src);
	else
		cpysize = dstsize - 1;
	if (dstsize != 0)
	{
		ft_memcpy(dst, src, cpysize);
		*(dst + cpysize) = '\0';
	}
	return (ft_strlen(src));
}
