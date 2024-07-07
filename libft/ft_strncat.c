/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:49:31 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/07 11:51:14 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src != '\0' && n--)
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}
