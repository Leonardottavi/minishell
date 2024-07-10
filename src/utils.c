/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:13:11 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 14:10:38 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy_environ(char **environ)
{
	int		i;
	int		count;
	char	**environ_copy;

	count = 0;
	i = 0;
	while (environ[count] != NULL)
		count++;
	environ_copy = malloc((count + 1) * sizeof(char *));
	if (environ_copy == NULL)
		return (NULL);
	while (i < count)
	{
		environ_copy[i] = ft_strdup(environ[i]);
		i++;
	}
	environ_copy[i] = NULL;
	return (environ_copy);
}

void	free_env(char **environ_copy)
{
	int	i;

	i = 0;
	while (environ_copy[i] != NULL)
	{
		free(environ_copy[i]);
		i++;
	}
	free(environ_copy);
}

char	*remove_newline(char *str)
{
	char *newline;

	newline = ft_strchr(str, '\n');
	if (newline)
		*newline = '\0';
	return (str);
}
