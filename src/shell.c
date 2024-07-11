/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:47 by lottavi           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/10 12:28:44 by lottavi          ###   ########.fr       */
=======
/*   Updated: 2024/07/10 18:43:24 by lottavi          ###   ########.fr       */
>>>>>>> LOTTAVI
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

<<<<<<< HEAD
=======
char	**get_args(char *input, char **args)
{
	int	i;

	i = 0;
	while (*input)
	{
		input = skip_whitespace(input);
		if (*input == '\0')
			break ;
		input = process_token(input, &args[i], &i);
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

>>>>>>> LOTTAVI
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
