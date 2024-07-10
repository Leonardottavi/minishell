/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:19:19 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 16:46:31 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	copy_until_dollar(char **result, char **start, size_t *result_len)
{
	char	*end;
	size_t	len_to_copy;

	end = ft_strchr(*start, '$');
	if (end)
		len_to_copy = (size_t)(end - *start);
	else
		len_to_copy = ft_strlen(*start);
	if (*result_len + len_to_copy >= MAX_BUFFER_SIZE)
	{
		printf("Errore: buffer overflow.\n");
		return (false);
	}
	ft_strncat(*result, *start, len_to_copy);
	*result_len += len_to_copy;
	*start += len_to_copy;
	return (true);
}

void	finalize_expansion(char **result, char *start, size_t *result_len)
{
	if (*result_len + ft_strlen(start) < MAX_BUFFER_SIZE)
	{
		ft_strcat(*result, start);
	}
	else
	{
		printf("Errore: buffer overflow.\n");
	}
}

bool	process_string(char **result, char **start, size_t *result_len)
{
	while (**start)
	{
		if (!copy_until_dollar(result, start, result_len))
		{
			free(*result);
			return (false);
		}
		if (**start == '$')
		{
			(*start)++;
			if (!expand_variable(result, start, result_len))
			{
				free(*result);
				return (false);
			}
		}
	}
	return (true);
}

char	*expander(char *input)
{
	char	*result;
	size_t	result_len;
	char	*start;

	result = malloc(MAX_BUFFER_SIZE);
	if (!result)
	{
		perror("malloc");
		return (NULL);
	}
	result[0] = '\0';
	result_len = 0;
	start = input;
	if (!process_string(&result, &start, &result_len))
	{
		return (NULL);
	}
	else
		process_string(&result, &start, &result_len);
	finalize_expansion(&result, start, &result_len);
	return (result);
}
