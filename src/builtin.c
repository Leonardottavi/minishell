/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:41 by lottavi           #+#    #+#             */
/*   Updated: 2024/06/30 14:29:25 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char* PATH;
char* builtin_commands[] = {"exit", "cd", "help", "pwd", "echo", "unset", "cat"}; // the built-in commands
int (*builtin_functions[]) (char**) = // the built-in functions
{
	&builtin_exit,
	&builtin_cd,
	&builtin_help,
	&builtin_pwd,
	&builtin_echo,
	&builtin_unset
};

int builtin_unset(char** args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "mini-shell: unset: a variable name is required\n");
        return 1;
    }
    int i = 1;
    while (args[i] != NULL) {
        if (unsetenv(args[i]) != 0) {
            perror("mini-shell");
        }
        i++;
    }
    return 1;
}

// mimics the 'cat' command by printing the contents of files passed as arguments
int builtin_cat(char** args) {
    int i = 1; // start from 1 to skip the command name
    while (args[i] != NULL) {
        FILE *file = fopen(args[i], "r");
        if (file == NULL) {
            perror("mini-shell");
            return 1; // continue to the next file if this one can't be opened
        }

        char line[1024];
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }

        fclose(file);
        i++;
    }
    return 1;
}

// echoes the arguments passed to it
int builtin_echo(char** args) {
    int i = 1; // start from 1 to skip the command name
    while (args[i] != NULL) {
        printf("%s", args[i]);
        if (args[i + 1] != NULL) printf(" "); // add a space between arguments, but not after the last one
        i++;
    }
    printf("\n"); // add a newline at the end
    return 1;
}

// prints the current working directory
int builtin_pwd(char** args __attribute__((unused)))
{
    char *cwd;
    cwd = getcwd(NULL, 0); // Dynamically allocate buffer size
    if (cwd != NULL) {
        printf("%s\n", cwd);
        free(cwd); // Free the allocated memory
    } else {
        perror("mini-shell");
    }
    return 1;
}

// exits out of the mini-shell
int builtin_exit(char** args __attribute__((unused)))
{
	return 0;
}

// changes the current directory
int builtin_cd(char** args) {
	if (NULL == args[1]) { // prints an error message if the user doesn't input the new directory
		fprintf(stderr, "mini-shell: please provide the new directory\n");
	} else if (chdir(args[1]) < 0) { // changes directory if the new one exists, otherwise prints an error message
		perror("mini-shell");
	}

	return 1;
}

// prints the available built-in commands and a short description for each of them
int builtin_help(char** args __attribute__((unused)))
{
	printf("Welcome to Lottavi's mini-shell!\n");
	printf("\tAvailable built-in commands\n:");
	printf("\t-exit(terminates the shell\n");
	printf("\t-cd(changes directory\n");
	printf("\t-help(lists the available built-in commands\n");
	printf("\t-history(lists all previous user inputs\n");
	return 1;
}
