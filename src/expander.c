/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:19:19 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/07 15:38:00 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	copy_until_dollar(char **result, char **start, size_t *result_len)
{
	char	*end;
	size_t	len_to_copy;

	end = ft_strchr(*start, '$');
	len_to_copy = end ? (size_t)(end - *start) : ft_strlen(*start);
	if (*result_len + len_to_copy >= MAX_BUFFER_SIZE)
	{
		printf("Errore: buffer overflow.\n");
		return false;
	}
	ft_strncat(*result, *start, len_to_copy);
	*result_len += len_to_copy;
	*start += len_to_copy;
	return (true);
}

bool	expand_variable(char **result, char **start, size_t *result_len)
{
	char *end = ft_strpbrk(*start, " $\n\t");
	if (!end) end = *start + ft_strlen(*start);
	char varName[256];
	if ((size_t)(end - *start) >= sizeof(varName)) {
		printf("Errore: nome variabile troppo lungo.\n");
		return (false);
	}
	ft_strncpy(varName, *start, end - *start);
	varName[end - *start] = '\0';
	char *varValue = getenv(varName);
	if (varValue)
	{
		size_t varValue_len = ft_strlen(varValue);
        if (*result_len + varValue_len >= MAX_BUFFER_SIZE)
		{
            printf("Errore: buffer overflow.\n");
            return false;
        }
        ft_strcat(*result, varValue);
        *result_len += varValue_len;
    }
    *start = end;
    return true;
}

void finalize_expansion(char **result, char *start, size_t *result_len) {
    if (*result_len + ft_strlen(start) < MAX_BUFFER_SIZE) {
        ft_strcat(*result, start);
    } else {
        printf("Errore: buffer overflow.\n");
    }
}

char *expander(char *input) {
    char *result = malloc(MAX_BUFFER_SIZE);
    if (!result) {
        perror("malloc");
        return NULL;
    }
    result[0] = '\0';
    size_t result_len = 0;

    char *start = input;
    while (*start) {
        if (!copy_until_dollar(&result, &start, &result_len)) {
            free(result);
            return NULL;
        }
        if (*start == '$') {
            start++; // Skip the dollar sign
            if (!expand_variable(&result, &start, &result_len)) {
                free(result);
                return NULL;
            }
        }
    }
    finalize_expansion(&result, start, &result_len);

    return result;
}


