/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:47 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 16:40:36 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

char	**get_args(char *input, char **args)
{
	char	*token;
	char	quote_char;
	int		in_quotes;
	int		i;

	quote_char = '\0';
	in_quotes = 0;
	i = 0;
	while (*input)
	{
		while ((*input > 8 && *input < 14) || *input == 32)
			input++;
		if (*input == '\0')
			break;
		if (*input == '"' || *input == '\'')
		{
			in_quotes = 1;
			quote_char = *input;
			input++;
		}
		token = input;
		while (*input && ((in_quotes && *input != quote_char) || (!in_quotes && !((*input > 8 && *input < 14) || *input == 32))))
			input++;
		if (in_quotes && *input == quote_char)
		{
			in_quotes = 0;
			*input = '\0';
			input++;
		}
		else if (!in_quotes && ((*input > 8 && *input < 14) || *input == 32))
		{
			*input = '\0';
			input++;
		}
		args[i] = remove_newline(token);
		i++;
	}
	args[i] = NULL;
	return (args);
}

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

char	*get_input(char *buffer)
{
	buffer = readline("minishell> ");
	if (NULL == buffer)
	{
		free(buffer);
		printf("exit\n");
		exit(0);
	}
	if (!all_whitespace(buffer))
		add_history(buffer);
	return (buffer);
}

int	main(void)
{
	char	*input;
	char	**args_buffer;
	int		result;
	int		i;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (init_resources(&input, &args_buffer) != 0)
		return (-1);
	result = main_loop(input, args_buffer);
	i = 0;
	while (args_buffer[i] != NULL)
	{
		free(args_buffer[i]);
		free_env(environ);
		i++;
	}
	free(args_buffer);
	return (result);
}
