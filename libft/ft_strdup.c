/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:54:48 by lottavi           #+#    #+#             */
/*   Updated: 2023/04/14 11:54:49 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		slen;
	char	*rptr;

	slen = ft_strlen(s1);
	rptr = (char *)malloc((slen + 1) * sizeof(char));
	if (rptr != NULL)
		ft_strlcpy(rptr, s1, slen + 1);
	return (rptr);
}
