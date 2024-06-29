/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:17 by lottavi           #+#    #+#             */
/*   Updated: 2024/06/29 14:09:54 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "../lib/libft.h"

#define MAX_BUFFER_SIZE 80 // buffer to hold user input
#define BUILTIN_COMMANDS 8 // number of bult-in commands

char PATH[1024]; // buffer to hold the home folder path
char* builtin_commands[] = {"exit", "cd", "help", "history", "env", "pwd", "echo", "unset"}; // the built-in commands

int builtin_unset(char** args);
int builtin_cat(char** args);
int builtin_exit(char** args);
int builtin_cd(char** args);
int builtin_help(char** args);
int builtin_history(char** args);
int builtin_env(char** args);
int builtin_pwd(char** args);
int builtin_echo(char** args);
int execute_without_pipe(char** args);
int execute_with_pipe(char** args);
void sigint_handler(int sig);
void save_history(char* input);
char* get_input(char* buffer);
char** get_args(char* input, char** args);
int (*builtin_functions[]) (char**) = {&builtin_exit, &builtin_cd, &builtin_help, &builtin_history, &builtin_env, &builtin_pwd, &builtin_echo, &builtin_unset};
