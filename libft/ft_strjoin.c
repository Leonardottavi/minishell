/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:54:59 by lottavi           #+#    #+#             */
/*   Updated: 2023/04/14 11:55:01 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	char	*rstr;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	rstr = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!rstr)
		return (NULL);
	ft_memcpy(rstr, s1, l1);
	ft_memcpy(rstr + l1, s2, l2);
	rstr[l1 + l2] = '\0';
	return (rstr);
}
