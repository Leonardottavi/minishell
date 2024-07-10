/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:08:57 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 14:09:00 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_with_pipe(char **args) {
	int num_pipes = 0;
	int i;
	int pipe_locations[64];
	pipe_locations[0] = -1;
	i = 0;
	while (args[i]) {
		if (strcmp(args[i], "|") == 0) {
			pipe_locations[++num_pipes] = i;
			args[i] = NULL;
		}
		i++;
	}
	int num_commands = num_pipes + 1;
	int pipes[num_pipes][2];
	i=0;
	while (i < num_pipes) {
		if (pipe(pipes[i]) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < num_commands) {
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
			int j = 0;
			while (j < num_pipes) {
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			char *cmd_path = get_cmd_path(args[pipe_locations[i] + 1]);
			execve(cmd_path, args + pipe_locations[i] + 1, environ);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < num_pipes) {
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i=0;
	while (i++ < num_commands) {
		wait(NULL);
	}
	return(1);
}
