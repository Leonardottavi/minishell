/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:40:00 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 15:55:49 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_end(char *start)
{
	char	*end;

	end = ft_strpbrk(start, " $\n\t\"");
	if (!end)
		end = start + ft_strlen(start);
	return (end);
}

bool	check_var_name_length(char *start, char *end, char *varName)
{
	if ((size_t)(end - start) >= sizeof(varName))
	{
		printf("Errore: nome variabile troppo lungo.\n");
		return (false);
	}
	return (true);
}

void	copy_var_name(char *varName, char *start, char *end)
{
	ft_strncpy(varName, start, end - start);
	varName[end - start] = '\0';
}

bool	handler_ext(char **result, char *varname,
	char *varvalue, size_t *result_len)
{
	if (varvalue)
	{
		if (!handle_var_value(result, varvalue, result_len))
			return (false);
	}
	else if (ft_strcmp(varname, "?") == 0)
	{
		if (!handle_exit_status(result, result_len))
			return (false);
	}
	else if (varname[0] == '\0')
	{
		if (!handle_empty_var_name(result, result_len))
			return (false);
	}
	return (true);
}

bool	expand_variable(char **result, char **start, size_t *result_len)
{
	char	varname[256];
	char	*end;
	char	*varvalue;

	end = get_end(*start);
	if (!check_var_name_length(*start, end, varname))
		return (false);
	copy_var_name(varname, *start, end);
	varvalue = getenv(varname);
	if (!handler_ext(result, varname, varvalue, result_len))
		return (false);
	*start = end;
	return (true);
}
