/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:47 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 12:28:44 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

char	*get_input(char *buffer)
{
	buffer = readline("minishell> ");
	if(NULL == buffer)
	{
		free(buffer);
		printf("exit\n");
		exit(0);
	}
	if (!all_whitespace(buffer))
		add_history(buffer);
	return (buffer);
}

int	init_resources(char **input, char ***args_buffer)
{
	*input = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
	if (NULL == *input)
	{
		perror("malloc");
		return (-1);
	}
	*args_buffer = (char **)malloc(sizeof(char *) * MAX_BUFFER_SIZE);
	if (NULL == *args_buffer)
	{
		perror("malloc");
		free(*input);
		return (-1);
	}
	return (0);
}

void free_args(char **args) {
	int i = 0;
	while (args[i] != NULL) {
		free(args[i]);
		i++;
	}
	free(args);
}

int	main_loop(char *input, char **args_buffer)
{
	char	**args;
	int		loop_status;
	char	*old_input;
	char *input_expanded;
	loop_status = 1;
	while (loop_status)
	{
		old_input = input;
		input = get_input(input);
		free(old_input);
		if (NULL == input || all_whitespace(input)
			|| input[0] == 0 || 0 == ft_strcmp(input, "\n"))
			continue ;
		else
		{
			if (strfind(input,'$')!=-1 && (strfind(input,'$')-strfind(input,'\''))!=1)
				input_expanded = expander(input);
			else
				input_expanded = strdup(input);
			args = get_args(input_expanded, args_buffer);
			redirection_control(args);
			loop_status = execute(args);
			free(input_expanded);
		}
	}
	free(input);
	return (0);
}

int	main(void)
{
	char	*input;
	char	**args_buffer;
	int		result;
	int		i;
	int		stdin_copy;
	int		stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	(void)stdin_copy;
	(void)stdout_copy;
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
