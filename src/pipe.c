/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:58:58 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 15:23:33 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pid_t spawn_proc(int in, int out, char **cmd)
// {
// 	pid_t pid;

// 	if ((pid = fork()) == 0)
// 	{
// 		if (in != 0)
// 		{
// 			dup2(in, 0);
// 			close(in);
// 		}
// 		if (out != 1)
// 		{
// 			dup2(out, 1);
// 			close(out);
// 		}
// 		char *cmd_path = get_cmd_path(cmd[0]);
// 		if (cmd_path != NULL)
// 		{
// 			execv(cmd_path, cmd);
// 			free(cmd_path);
// 		}
// 		else
// 		{
// 			printf("Command not found--are you using some kind of weed?\n");
// 		}
// 		exit(1);
// 	}
// 	return(pid);
// }

// int	execute_with_pipe(char **args)
// {
// 	int		i = 0;
// 	int		in = 0;
// 	int		fd[2];
// 	char	**cmd = args;
// 	pid_t	pid;

// 	while (args[i])
// 	{
// 		if (ft_strcmp(args[i], "|") == 0)
// 		{
// 			args[i] = NULL;
// 			pipe(fd);
// 			pid = spawn_proc(in, fd[1], cmd);
// 			close(fd[1]);
// 			in = fd[0];
// 			cmd = args + i + 1;
// 		}
// 		i++;
// 	}
// 	if (in != 0)
// 		dup2(in, 0);
// 	char *cmd_path = get_cmd_path(cmd[0]);
// 	if (cmd_path != NULL)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 			signal(SIGQUIT, SIG_DFL);
// 			execv(cmd_path, cmd);
// 			free(cmd_path);
// 			exit(1);
// 		}
// 		else
// 		{
// 			signal(SIGINT, SIG_IGN);
// 			signal(SIGQUIT, SIG_IGN);

// 			int status;
// 			waitpid(pid, &status, 0);  /* Wait for the child process to finish */
// 		}
// 	}
// 	else
// 		printf("Command not found--are you using some kind of weed?\n");
// 	return 1;
// }



int execute_with_pipe(char **args) {
    int num_pipes = 0;
    int i;
    int pipe_locations[64]; // Array to store locations of pipes
    pipe_locations[0] = -1; // Initial value indicating no pipe before the first command

    // Find pipe locations in args array
    i = 0;
    while (args[i]) {
        if (strcmp(args[i], "|") == 0)
        {
            pipe_locations[++num_pipes] = i; // Store the index of pipe symbol
            args[i] = NULL; // Replace "|" with NULL to mark end of arguments for execv
        }
        i++;
    }

    int num_commands = num_pipes + 1; // Number of commands to be executed
    int pipes[num_pipes][2]; // Array to store pipes

    // Create pipes
    i=0;
    while (i < num_pipes) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Execute commands using fork and execv
    i = 0;
    while (i < num_commands) {
        pid_t pid;
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process

            // Set up stdin redirection for all but first command
            if (i > 0) {
                if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // Set up stdout redirection for all but last command
            if (i < num_pipes) {
                if (dup2(pipes[i][1], STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // Close all pipe fds
            int j = 0;
            while (j < num_pipes) {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }

            // Execute the command
            execvp(args[pipe_locations[i] + 1], &args[pipe_locations[i] + 1]);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Close all pipe fds in parent process
    i = 0;
    while (i < num_pipes)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }


    i=0;
    while (i++ < num_commands)
        wait(NULL);
	return(1);
}