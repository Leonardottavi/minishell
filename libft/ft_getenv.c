/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:00:25 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/05 18:02:33 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char **envp, const char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			return (&envp[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}
