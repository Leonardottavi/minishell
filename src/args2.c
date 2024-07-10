/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:36:23 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 12:38:51 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!((s[i] > 8 && s[i] < 14) || s[i] == 32))
			return (0);
		i++;
	}
	return (1);
}

char	**get_args(char *input, char **args)
{
	int		i;
	char	*token;
	char	quote_char;
	int		in_quotes;

	in_quotes = 0;
	quote_char = '\0';
	i = 0;
	while (*input)
	{
		skip_whitespace(&input);
		if (*input == '\0')
			break ;
		handle_quotes(&input, &in_quotes, &quote_char);
		token = input;
		find_end_of_token(&input, in_quotes, quote_char);
		handle_end_of_token(&input, &in_quotes);
		args[i] = remove_newline(token);
		i++;
	}
	args[i] = NULL;
	return (args);
}
