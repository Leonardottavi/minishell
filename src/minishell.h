/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:17 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/11 14:06:07 by lottavi          ###   ########.fr       */
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

# define MAX_BUFFER_SIZE 1000 // buffer to hold user input
# define BUILTIN_COMMANDS 8 // number of bult-in commands
# define SIGNALS 3 // number of signals

typedef struct t_pipe
{
	int	num_pipes;
	int	num_commands;
	int	pipe_locations[64];
	int	pipes[100][2];
}		t_pipe;

extern int		g_exit_status;
extern char		**environ;
int				ft_strfind(char *str, char p);
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
int				all_whitespace(char *s);
int				init_resources(char **input, char ***args_buffer);

//args
char			**get_args(char *input, char **args);
char			*skip_whitespace(char *input);
char			*process_token(char *input, char **arg, int *i);
char			*find_token_end(char *input,
					char quote_char, int in_quotes);
char			*handle_end_of_token(char *input,
					int in_quotes, char quote_char);
char			*rm_line(char *str);
//function executers
int				execute(char **args);

//pipe functions
int				count_pipes_and_commands(char **args, t_pipe *data);
void			close_pipes(t_pipe *data);
void			create_pipes(t_pipe *data);
void			exe_pipe(int i, t_pipe *data, char **args);
void			setup_pipe(int i, t_pipe *data);
void			wait_for_commands(t_pipe *data);
void			initialize_pipes_and_commands(char **args, t_pipe *data);
void			exe_pipe2(t_pipe *data, char **args);
int				execute_with_pipe(char **args);

//signals
void			sigint_handler(pid_t pid);

//no pipe execute
char			*get_cmd_path(char *cmd);
int				execute_without_pipe(char **args);

//redirect functions
void			redirection_ft_control(char **args);
void			redirect_heredoc(char **args, int i);

//utils
char			**ft_copy_environ(char **environ);
void			free_env(char **environ_copy);
char			*remove_newline(char *str);
int				ft_strfind(char *str, char p);

//expansion
char			*expander(char *input);
bool			expand_variable(char **result,
					char **start, size_t *result_len);
bool			handle_var_value(char **result,
					char *varvalue, size_t *result_len);
bool			handle_exit_status(char **result, size_t *result_len);
bool			handle_empty_var_name(char **result, size_t *result_len);

#endif
