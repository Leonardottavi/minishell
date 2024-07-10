/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:17 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 10:26:36 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define MAX_BUFFER_SIZE 10000 // buffer to hold user input
# define BUILTIN_COMMANDS 8 // number of bult-in commands
# define SIGNALS 3 // number of signals

extern int		g_exit_status;
extern char		**environ;
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
char			*get_input(char *buffer);
char			**get_args(char *input, char **args);
int				main_loop(char *input, char **args_buffer);

//function executers
int				execute(char **args);

//pipe functions
int				execute_with_pipe(char **args);

//signals
void			sigint_handler(pid_t pid);

//no pipe execute
char			*get_cmd_path(char *cmd);
int				execute_without_pipe(char **args);

//redirect functions
void			redirection_control(char **args);
void			redirect_heredoc(char **args, int i);

//utils
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void			free_env(char **environ_copy);

//expansion
char			*expander(char *input);

#endif
