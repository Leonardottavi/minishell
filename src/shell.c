/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:47 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/03 11:41:25 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum __attribute__((unused)))
{
	printf("minishell: killed\n");
	exit(0);
}

char	**get_args(char *input, char **args)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	token = ft_strtok(input, " ");
	while (NULL != token)
	{
		args[i] = token;
		token = ft_strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	j = 0;
	while (NULL != args[j])
	{
		args[j] = ft_strtok(args[j], "\n");
		j++;
	}
	return (args);
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

int	main_loop(char *input, char **args_buffer)
{
	char	**args;
	int		loop_status;
	char	*old_input;

	loop_status = 1;
	while (loop_status)
	{
		old_input = input;
		input = get_input(input);
		free(old_input);
		if (32 == input[0] || 9 == input[0]
			|| 0 == ft_strcmp(input, "\n") || NULL == input)
			continue ;
		else
		{
			save_history(input);
			args = get_args(input, args_buffer);
			loop_status = execute(args);
		}
	}
	return (0);
}

int	main(void)
{
	char	*input;
	char	**args_buffer;
	int		result;
	int		i;

	signal(SIGINT, sigint_handler);
	if (init_resources(&input, &args_buffer) != 0)
	{
		return (-1);
	}
	result = main_loop(input, args_buffer);
	i = 0;
	while (args_buffer[i] != NULL)
	{
		free(args_buffer[i]);
		i++;
	}
	free(args_buffer);
	return (result);
}
