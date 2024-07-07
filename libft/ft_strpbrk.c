/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:31:02 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/07 11:36:38 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *s, const char *accept)
{
	const char	*a_ptr;

	while (*s != '\0')
	{
		a_ptr = accept;
		while (*a_ptr != '\0')
		{
			if (*s == *a_ptr)
			{
				return ((char *)s);
			}
			a_ptr++;
		}
		s++;
	}
	return (NULL);
}
