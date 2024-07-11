/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:27:20 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/11 14:06:07 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	*process_input(char *input)
{
	char	*input_expanded;

	if (ft_strfind(input, '$') != -1
		&& (ft_strfind(input, '$') - ft_strfind(input, '\'')) != 1)
		input_expanded = expander(input);
	else
		input_expanded = strdup(input);
	return (input_expanded);
}

int	main_loop(char *input, char **args_buffer)
{
	char	**args;
	int		loop_status;
	char	*old_input;
	char	*input_expanded;

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
			input_expanded = process_input(input);
			args = get_args(input_expanded, args_buffer);
			redirection_ft_control(args);
			loop_status = execute(args);
			free(input_expanded);
		}
	}
	free(input);
	return (0);
}
