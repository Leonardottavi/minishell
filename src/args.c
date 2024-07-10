/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:28:05 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 12:36:42 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_newline(char *str)
{
	char	*newline;

	newline = ft_strchr(str, '\n');
	if (newline)
		*newline = '\0';
	return (str);
}

void	skip_whitespace(char **input)
{
	while ((**input > 8 && **input < 14) || **input == 32)
		(*input)++;
}

void	handle_quotes(char **input, int *in_quotes, char *quote_char)
{
	if (**input == '"' || **input == '\'')
	{
		*in_quotes = 1;
		*quote_char = **input;
		(*input)++;
	}
}

void	find_end_of_token(char **input, int in_quotes, char quote_char)
{
	while (**input && ((in_quotes && **input != quote_char)
			|| ((!in_quotes && !(**input > 8 && **input < 14))
				|| **input == 32)))
		(*input)++;
}

void	handle_end_of_token(char **input, int *in_quotes)
{
	if (*in_quotes && (**input == '"' || **input == '\''))
	{
		*in_quotes = 0;
		**input = '\0';
		(*input)++;
	}
	else if (!*in_quotes && ((**input > 8 && **input < 14) || **input == 32))
	{
		**input = '\0';
		(*input)++;
	}
}
