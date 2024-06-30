/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:20 by lottavi           #+#    #+#             */
/*   Updated: 2024/06/30 19:54:31 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_without_pipe(char** args)
{
	pid_t child_process_id;
	child_process_id = fork();
	if (-1 == child_process_id)
	{
		printf("Failed!\n");
		exit(EXIT_FAILURE);
	}
	if (0 == child_process_id)
	{
		if (-1 == execvp(args[0], args))
			printf("Command not found--are you using some kind of weed?\n");
		exit(1);
	} else {
		wait(NULL);
	}
	return (1);
}

int execute_with_pipe(char** args) {
	int i = 0;
	char* left_side[3];
	char* right_side[3];
	while (0 != strcmp(args[i], "|"))
	{
		left_side[i] = args[i];
		i++;
	}
	left_side[i] = NULL;
	i++;
	int j = 0;
	while (args[i] != NULL)
	{
		right_side[j] = args[i];
		i++;
		j++;
	}
	right_side[j] = NULL;
	int fd[2];
	if (-1 == pipe(fd))
	{
		printf("Piping failed for some reason!\n");
		exit(EXIT_FAILURE);
	}
	pid_t child_process_id;
	int child_status;
	pid_t child_process_id2;
	int child_status2;
	child_process_id = fork();
	if(-1 == child_process_id)
	{
		printf("Fork failed for some reason!\n");
		exit(EXIT_FAILURE);
	} else if (0 == child_process_id)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (-1 == execvp(left_side[0], left_side))
			printf("Command not found--Did you mean something else?\n");
		exit(1);
	}
	child_process_id2 = fork();
	if (-1 == child_process_id2)
	{
		printf("Fork failed for some reason!\n");
		exit(EXIT_FAILURE);
	} else if (0 == child_process_id2)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (-1 == execvp(right_side[0], right_side))
			printf("Command not found--Did you mean something else?\n");
		exit(1);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(child_process_id, &child_status, 0); // waits execution of the 1st child
		waitpid(child_process_id2, &child_status2, 0); // waits execution of the 2nd child
	}
	return (1);
}

int execute(char** args) {
	int j = 0;
	int loop_status;
	int i;
	i = 0;
	while (i < BUILTIN_COMMANDS)
	{
		if (0 == strcmp(args[0], g_builtin_commands[i]))
		{
			loop_status = (*builtin_functions[i])(args);
			return loop_status;
		}
		i++;
	}
	while (NULL != args[j])
	{
		if (0 == strcmp(args[j], "|")) {
			loop_status = execute_with_pipe(args);
			return loop_status;
		}
		j++;
	}
	loop_status = execute_without_pipe(args);
	return (loop_status);
}
