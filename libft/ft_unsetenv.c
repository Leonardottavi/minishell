/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:01:01 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/01 14:34:54 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

extern char	**environ;

int	ft_unsetenv(const char *name)
{
	char	**env;
	char	*entry;
	size_t	len;

	env = environ;
	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
	{
		return (-1);
	}
	len = ft_strlen(name);
	while (entry != NULL)
	{
		entry = *env;
		if (ft_strncmp(entry, name, len) == 0 && entry[len] == '=')
		{
			while (env[0] != NULL)
			{
				*env = *(env + 1);
				env++;
			}
			return (0);
		}
		env++;
	}
	return (0);
}
