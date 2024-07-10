/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:22:48 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 19:01:22 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(int i, int num_pipes, int pipes[][2])
{
	if (i > 0)
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (i < num_pipes)
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

void	wait_for_commands(int num_commands)
{
	int	i;

	i = 0;
	while (i++ < num_commands)
	{
		wait(NULL);
	}
}

void	initialize_pipes_and_commands(char **args, int *num_pipes,
	int *num_commands, int *pipe_locations)
{
	count_pipes_and_commands(args, num_pipes, num_commands, pipe_locations);
}

void	exe_pipe2(int num_commands, int num_pipes,
	int pipes[][2], char **args, int *pipe_locations)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		exe_pipe(i, num_pipes, pipes, args, pipe_locations);
		i++;
	}
}
