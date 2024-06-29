/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:20 by lottavi           #+#    #+#             */
/*   Updated: 2024/06/29 19:23:01 by lottavi          ###   ########.fr       */
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

// executes terminal built-in commands by feeding the output of the first command into the input of the second command
int execute_with_pipe(char** args) {
	int i = 0;
	char* left_side[3]; // stores the first command together with a flag and NULL
	char* right_side[3]; // stores the second command together with a flag and NULL
	while (0 != strcmp(args[i], "|")) { // saves the tokens on the left side of the pipe character into a character array
		left_side[i] = args[i];
		i++;
	}
	left_side[i] = NULL; // adds NULL as the last token of the first command
	i++; // skips the pipe character so it doesn't get stored
	int j = 0;
	while (args[i] != NULL) { // saves the tokens on the right side of the pipe character into a character array
		right_side[j] = args[i];
		i++;
		j++;
	}
	right_side[j] = NULL; // adds NULL as the last token of the second command
	int fd[2]; // stores the file descriptors
	if (-1 == pipe(fd)) { // starts piping
		printf("Piping failed for some reason!\n");
		exit(EXIT_FAILURE);
	}
	pid_t child_process_id;
	int child_status;
	pid_t child_process_id2;
	int child_status2;
	child_process_id = fork();
	if(-1 == child_process_id) {
		printf("Fork failed for some reason!\n");
		exit(EXIT_FAILURE);
	} else if (0 == child_process_id) { // 1st child
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (-1 == execvp(left_side[0], left_side)) {
			printf("Command not found--Did you mean something else?\n");
		}
		exit(1);
	}
	child_process_id2 = fork();
	if (-1 == child_process_id2) {
		printf("Fork failed for some reason!\n");
		exit(EXIT_FAILURE);
	} else if (0 == child_process_id2) { // 2nd child
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (-1 == execvp(right_side[0], right_side)) {
			printf("Command not found--Did you mean something else?\n");
		}
		exit(1);
	} else { // parent
		close(fd[0]);
		close(fd[1]);
		waitpid(child_process_id, &child_status, 0); // waits execution of the 1st child
		waitpid(child_process_id2, &child_status2, 0); // waits execution of the 2nd child
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
