/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:58:58 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/01 18:23:09 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipe_args(char **args, char **left_side, char **right_side)
{
	int	i;
	int	j;

	i = 0;
	while (0 != strcmp(args[i], "|"))
	{
		left_side[i] = args[i];
		i++;
	}
	j = 0;
	left_side[i] = NULL;
	i++;
	while (args[i] != NULL)
	{
		right_side[j] = args[i];
		i++;
		j++;
	}
	right_side[j] = NULL;
}

void	failed_pipe(int fd[2])
{
	if (-1 == pipe(fd))
	{
		printf("Piping failed for some reason!\n");
		exit(EXIT_FAILURE);
	}
}

void	execute_left_side(int fd[2], char **left_side)
{
	pid_t	child_process_id;

	child_process_id = fork();
	if (-1 == child_process_id)
	{
		printf("Fork failed for some reason!\n");
		exit(EXIT_FAILURE);
	}
	else if (0 == child_process_id)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (-1 == execvp(left_side[0], left_side))
			printf("Command not found--Did you mean something else?\n");
		exit(1);
	}
}

void	execute_right_side(int fd[2], char **right_side)
{
	pid_t	child_process_id;

	child_process_id = fork();
	if (-1 == child_process_id)
	{
		printf("Fork failed for some reason!\n");
		exit(EXIT_FAILURE);
	}
	else if (0 == child_process_id)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (-1 == execvp(right_side[0], right_side))
			printf("Command not found--Did you mean something else?\n");
		exit(1);
	}
}

void	wait_for_children(pid_t child1, pid_t child2)
{
	int	child_status;

	waitpid(child1, &child_status, 0);
	waitpid(child2, &child_status, 0);
}

