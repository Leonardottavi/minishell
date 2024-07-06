/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:13:11 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 18:21:02 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_copy_environ(char **environ)
{
	int i = 0, count = 0;

	while (environ[count] != NULL)
		count++;

	char **environ_copy = malloc((count + 1) * sizeof(char *));
	if (environ_copy == NULL)
		return NULL;

	while (i < count)
	{
		environ_copy[i] = ft_strdup(environ[i]);
		i++;
	}
	environ_copy[i] = NULL;

	return environ_copy;
}

void	free_environ_copy(char **environ_copy)
{
	int i = 0;
	while (environ_copy[i] != NULL)
	{
		free(environ_copy[i]);
		i++;
	}
	free(environ_copy);
}
