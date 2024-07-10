/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:42:58 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 18:43:27 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_whitespace(char *input)
{
	while ((*input > 8 && *input < 14) || *input == 32)
		input++;
	return (input);
}

char	*process_token(char *input, char **arg, int *i)
{
	char	*token;
	char	quote_char;
	int		in_quotes;

	in_quotes = 0;
	quote_char = '\0';
	if (*input == '"' || *input == '\'')
	{
		in_quotes = 1;
		quote_char = *input++;
	}
	token = input;
	input = find_token_end(input, quote_char, in_quotes);
	input = handle_end_of_token(input, in_quotes, quote_char);
	*arg = rm_line(token);
	(*i)++;
	return (input);
}

char	*find_token_end(char *input, char quote_char, int in_quotes)
{
	while (*input && ((in_quotes && *input != quote_char)
			|| (!in_quotes && !((*input > 8 && *input < 14) || *input == 32))))
	{
		input++;
	}
	return (input);
}

char	*handle_end_of_token(char *input, int in_quotes, char quote_char)
{
	if (in_quotes && *input == quote_char)
	{
		*input++ = '\0';
	}
	else if (!in_quotes && ((*input > 8 && *input < 14) || *input == 32))
	{
		*input++ = '\0';
	}
	return (input);
}

char	*rm_line(char *str)
{
	char	*p;

	p = str;
	while (*p)
	{
		if (*p == '\n')
		{
			*p = '\0';
			break ;
		}
		p++;
	}
	return (str);
}
