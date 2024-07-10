/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_varriable2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:51:14 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 15:51:36 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_var_value(char **result, char *varvalue, size_t *result_len)
{
	size_t	varvalue_len;

	varvalue_len = ft_strlen(varvalue);
	if (*result_len + varvalue_len >= MAX_BUFFER_SIZE)
	{
		printf("Errore: buffer overflow.\n");
		return (false);
	}
	ft_strcat(*result, varvalue);
	*result_len += varvalue_len;
	return (true);
}

bool	handle_exit_status(char **result, size_t *result_len)
{
	char	exit_status_str[4];
	size_t	exit_status_len;

	sprintf(exit_status_str, "%d", g_exit_status);
	exit_status_len = ft_strlen(exit_status_str);
	if (*result_len + exit_status_len >= MAX_BUFFER_SIZE)
	{
		printf("Errore: buffer overflow.\n");
		return (false);
	}
	ft_strcat(*result, exit_status_str);
	*result_len += exit_status_len;
	return (true);
}

bool	handle_empty_var_name(char **result, size_t *result_len)
{
	if (*result_len + 1 >= MAX_BUFFER_SIZE)
	{
		printf("Errore: buffer overflow.\n");
		return (false);
	}
	ft_strcat(*result, "$");
	(*result_len)++;
	return (true);
}
