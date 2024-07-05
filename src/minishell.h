/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:17 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/05 13:53:33 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "../libft/libft.h"

# define MAX_BUFFER_SIZE 80 // buffer to hold user input
# define BUILTIN_COMMANDS 8 // number of bult-in commands
# define SIGNALS 3 // number of signals

extern char		g_path[1024];
char			**get_builtin_commands(void);
int				(*(*get_builtin_functions(void))[])(char **);

int				builtin_exit(char **args);
int				builtin_cd(char **args);
int				builtin_help(char **args);
int				builtin_env(char **args);
int				builtin_pwd(char **args);
int				builtin_echo(char **args);
int				builtin_unset(char **args);
int				builtin_export(char **args);

// function shell
void			save_history(char *input);
char			*get_input(char *buffer);
char			**get_args(char *input, char **args);
int				main_loop(char *input, char **args_buffer);

//function executers
int				execute_without_pipe(char **args);
int				execute_with_pipe(char **args);
int				execute(char **args);

//pipe functions
void			parse_pipe_args(char **args, char **left_side,
					char **right_side);
void			failed_pipe(int fd[2]);
void			execute_left_side(int fd[2], char **left_side);
void			execute_right_side(int fd[2], char **right_side);
void			process_checker(pid_t child1, pid_t child2);

//signals
void			sigint_handler(int signum __attribute__((unused)));
void			sigquit_handler(int signum __attribute__((unused)));

#endif
