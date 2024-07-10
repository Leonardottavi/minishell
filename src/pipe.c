/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:14:23 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 17:26:07 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes_and_commands(char **args, int *num_pipes,
	int *num_commands, int *pipe_locations)
{
	int	i;

	i = 0;
	pipe_locations[0] = -1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			pipe_locations[++(*num_pipes)] = i;
			args[i] = NULL;
		}
		i++;
	}
	*num_commands = *num_pipes + 1;
	return (i);
}

void	close_pipes(int num_pipes, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	create_pipes(int num_pipes, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	exe_pipe(int i, int num_pipes, int pipes[][2],
	char **args, int *pipe_locations)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_pipe(i, num_pipes, pipes);
		close_pipes(num_pipes, pipes);
		cmd_path = get_cmd_path(args[pipe_locations[i] + 1]);
		execve(cmd_path, args + pipe_locations[i] + 1, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	execute_with_pipe(char **args)
{
	int	num_pipes;
	int	num_commands;
	int	pipe_locations[64];

	num_pipes = 0;
	num_commands = 0;
	int	pipes[num_pipes][2];
	initialize_pipes_and_commands(args, &num_pipes,
		&num_commands, pipe_locations);
	create_pipes(num_pipes, pipes);
	exe_pipe2(num_commands, num_pipes, pipes, args, pipe_locations);
	close_pipes(num_pipes, pipes);
	wait_for_commands(num_commands);
	return (1);
}
