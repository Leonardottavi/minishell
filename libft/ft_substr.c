/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:55:59 by lottavi           #+#    #+#             */
/*   Updated: 2023/04/14 11:56:01 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*subs;
	size_t	reallen;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		reallen = ft_strlen(s + start);
	else
		reallen = len;
	subs = (char *)malloc((reallen + 1) * sizeof(char));
	if (!subs)
		return (NULL);
	while (i < reallen && ft_strlen(s) >= start)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
