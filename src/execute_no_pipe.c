/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:54:00 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 11:57:53 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	fork_process(void)
{
	pid_t	process_id;

	process_id = fork();
	if (-1 == process_id)
	{
		printf("Failed!\n");
		exit(EXIT_FAILURE);
	}
	return (process_id);
}

void	execute_command(char **args)
{
	char	*cmd_path;

	if (args[0] != NULL && strncmp(args[0], "/bin/", 5) == 0)
	{
		if (-1 == execve(args[0], args, environ))
		{
			perror("Failed to execute command");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cmd_path = get_cmd_path(args[0]);
		if (cmd_path != NULL)
		{
			if (-1 == execve(cmd_path, args, environ))
				printf("Command not found\n");
			free(cmd_path);
		}
		else
			printf("Command not found\n");
	}
	exit(EXIT_FAILURE);
}

void	wait_for_child(pid_t process_id __attribute__((unused)))
{
	int	status;

	wait(&status);
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return ;
}

int	execute_without_pipe(char **args)
{
	pid_t	process_id;

	process_id = fork_process();
	if (0 == process_id)
	{
		signal(SIGINT, sigint_handler);
		execute_command(args);
	}
	else
	{
		wait_for_child(process_id);
	}
	signal(SIGINT, sigint_handler);
	return (1);
}
