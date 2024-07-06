/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:24:50 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 17:25:47 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void write_to_pipe(int *pipefd, char *delimiter)
{
	close(pipefd[0]);
	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, stdin) != -1)
	{
		if (strcmp(line, delimiter) == 0)
			break;
		write(pipefd[1], line, strlen(line));
	}
	free(line);
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

void read_from_pipe(int *pipefd, char **args, int i)
{
	wait(NULL);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	args[i] = NULL;
}

void redirect_heredoc(char **args, int i)
{
	int pipefd[2];
	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		write_to_pipe(pipefd, args[i + 1]);
	}
	else
	{
		read_from_pipe(pipefd, args, i);
	}
}
