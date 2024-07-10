/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:13:11 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 10:25:12 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	if (new_size == 0) {
		free(ptr);
		return NULL;
	}

	if (ptr == NULL) {
		return malloc(new_size);
	}

	if (new_size <= old_size) {
		return ptr;
	}

	new_ptr = malloc(new_size);
	if (new_ptr) {
		memcpy(new_ptr, ptr, old_size);
		free(ptr);
	} else {
		free(ptr);
	}

	return new_ptr;
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
