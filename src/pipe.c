/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:08:57 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 15:02:40 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes_and_commands(char **args, int *num_pipes, int *num_commands, int *pipe_locations)
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

void close_pipes(int num_pipes, int pipes[][2]) {
	int i = 0;
	while (i < num_pipes) {
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void create_pipes(int num_pipes, int pipes[][2]) {
	int i = 0;
	while (i < num_pipes) {
		if (pipe(pipes[i]) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void pipe_exe(int i, int num_pipes, int pipes[][2], char **args, int *pipe_locations) {
	pid_t pid;
	if ((pid = fork()) == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		if (i > 0) {
			if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1) {
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
		if (i < num_pipes) {
			if (dup2(pipes[i][1], STDOUT_FILENO) == -1) {
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
		close_pipes(num_pipes, pipes);
		char *cmd_path = get_cmd_path(args[pipe_locations[i] + 1]);
		execve(cmd_path, args + pipe_locations[i] + 1, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void wait_for_commands(int num_commands) {
	int i = 0;
	while (i++ < num_commands) {
		wait(NULL);
	}
}

int execute_with_pipe(char **args) {
	int num_pipes = 0;
	int num_commands = 0;
	int pipe_locations[64];
	int i = count_pipes_and_commands(args, &num_pipes, &num_commands, pipe_locations);
	int pipes[num_pipes][2];
	create_pipes(num_pipes, pipes);
	i = 0;
	while (i < num_commands) {
		pipe_exe(i, num_pipes, pipes, args, pipe_locations);
		i++;
	}
	close_pipes(num_pipes, pipes);
	wait_for_commands(num_commands);
	return 1;
}
