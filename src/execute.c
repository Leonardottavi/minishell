/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:20 by lottavi           #+#    #+#             */
/*   Updated: 2024/06/30 17:36:15 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// executes terminal built-in commands in a separate process
int execute_without_pipe(char** args) {
	pid_t child_process_id; // stores the child process's id
	child_process_id = fork(); // initializes the separate process making a copy of teh current one
	if (-1 == child_process_id) { // if forking fails, prints an error message
		printf("Failed!\n");
		exit(EXIT_FAILURE);
	}
	if (0 == child_process_id) { // goes into the child process
		if (-1 == execvp(args[0], args)) { // executes the terminal built-in command, otherwise prints an error message
			printf("Command not found--are you using some kind of weed?\n");
		}
		exit(1);
	} else {
		wait(NULL); // waits for the child to finish execution
	}

	return 1;
}

// decides which execution to run based on user input
int execute(char** args) {
	int j = 0;
	int loop_status;
	int i;
	i = 0;
	while (i < BUILTIN_COMMANDS) // if the user inputs a built-in command, executes it
	{
		if (0 == strcmp(args[0], builtin_commands[i]))
		{
			loop_status = (*builtin_functions[i])(args);
			return loop_status;
		}
		i++;
	}
	while (NULL != args[j]) { // if the user inputs the pipe character, executes the execute_with_pipe function
		if (0 == strcmp(args[j], "|")) {
			loop_status = execute_with_pipe(args);
			return loop_status;
		}
		j++;
	}
	loop_status = execute_without_pipe(args); // if the user inputs a terminal built-in command, executes the execute_without_pipe function

	return loop_status;
}
