/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:47 by lottavi           #+#    #+#             */
/*   Updated: 2024/06/29 15:31:19 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// kills the program
void sigint_handler()
{
	printf("minishell: killed\n");
	exit(0);
}

// saves the history of user inputs into a hidden file called history.txt located in the home folder
void save_history(char* input)
{
	strcat(strcpy(PATH, getenv("HOME")), "/.history.txt"); // concatenates the file name with the home directory path
	FILE* history = fopen(PATH, "a"); // opens the file in append mode (creates a new file if it doesn't already exists, otherwise it adds to it without overwriting it)
	fprintf(history, "%s", input); // writes user inputs in the file
	fclose(history); // closes the file
}

// gets user input
char* get_input(char* buffer)
{
	printf("mini-shell>"); // the shell prompt
	fgets(buffer, MAX_BUFFER_SIZE, stdin); // scans the whole user input as a single string

	return buffer;
}

// processes user input by tokenizing each word
char** get_args(char* input, char** args)
{
	int i = 0;
	char* token = strtok(input, " ");
	while (NULL != token) { // tokenizes user input
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL; // sets the last token to NULL
	int j = 0;
	while (NULL != args[j]) { // removes the newline character from each token
		args[j] = strtok(args[j], "\n");
		j++;
	}

	return args;
}

int main()
{
	signal(SIGINT, sigint_handler); // kills the program with ctrl-c

	char* input = (char*)malloc(sizeof(char) * MAX_BUFFER_SIZE); // allocates memory on the heap for user input
	if (NULL == input) {
		perror("malloc");
		return -1;
	}
	char** args_buffer = (char**)malloc(sizeof(char*) * MAX_BUFFER_SIZE); // allocates memory on the heap for the tokens
	if (NULL == args_buffer) {
		perror("malloc");
		return -1;
	}
	char** args; // initializes the variable that refers to the tokens
	int loop_status = 1; // initializes the variable that makes the loop run forever unless the exit function is called, which changes it to 0

	while(loop_status) {
		input = get_input(input);
		if (32 == input[0] || 9 == input[0] || 0 == strcmp(input, "\n") || NULL == input) { // if the user inputs spaces, tabs, returns, or NULL is assigned to the input, just asks for input again
			continue;
		} else {
			save_history(input); // saves user input to be retrieved as history
			args = get_args(input, args_buffer); // tokenizes user input
			loop_status = execute(args); // executes the commands
		}
	}
	free(input);
	free(args);

	return 0;
}
