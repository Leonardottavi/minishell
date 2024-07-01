/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:33:42 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/01 17:51:22 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s1, const char *s2)
{
	size_t		count;

	count = 0;
	while (*s1)
	{
		if (ft_strchr(s2, *s1))
			count++;
		else
			break ;
		s1++;
	}
	return (count);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	while (s[i] != '\0')
	{
		i2 = 0;
		while (reject[i2] != '\0')
		{
			if (s[i] == reject[i2])
				return (i);
			i2++;
		}
		i++;
	}
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_get_next_token(char *str, const char *delim, char **saveptr)
{
	char	*end;

	if (str == NULL)
		str = *saveptr;
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	str += ft_strspn(str, delim);
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	end = str + ft_strcspn(str, delim);
	if (*end == '\0')
	{
		*saveptr = end;
		return (str);
	}
	*end = '\0';
	*saveptr = end + 1;
	return (str);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saveptr;

	return (ft_get_next_token(str, delim, &saveptr));
}
