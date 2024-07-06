/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:20 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 17:43:37 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **args)
{
	int	i;

	i = 0;
	while (i < BUILTIN_COMMANDS)
	{
		if (0 == ft_strcmp(args[0], get_builtin_commands()[i]))
			return ((*get_builtin_functions())[i](args));
		i++;
	}
	return (-1);
}

char *get_cmd_path(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy = ft_strdup(path);
	char *dir = ft_strtok(path_copy, ":");

	while (dir != NULL)
	{
		char *cmd_path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
		ft_strcpy(cmd_path, dir);
		ft_strcat(cmd_path, "/");
		ft_strcat(cmd_path, cmd);

		if (access(cmd_path, X_OK) == 0)
		{
			free(path_copy);
			return cmd_path;
		}

		free(cmd_path);
		dir = ft_strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}


int execute_without_pipe(char **args)
{
	pid_t process_id;
	signal(SIGINT, SIG_IGN);
	process_id = fork();
	if (-1 == process_id)
	{
		printf("Failed!\n");
		exit(EXIT_FAILURE);
	}
	if (0 == process_id)
	{
		signal(SIGINT, sigint_handler);
		char *cmd_path = get_cmd_path(args[0]);
		if (cmd_path != NULL)
		{
			if (-1 == execv(cmd_path, args))
				printf("Command not found--are you using some kind of weed?\n");
			free(cmd_path);
		}
		else
		{
			printf("Command not found--are you using some kind of weed?\n");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		wait(&status);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (1);
	}
	signal(SIGINT, sigint_handler);
	return (1);
}

int	execute(char **args)
{
	int	j;
	int	loop_status;

	j = 0;
	loop_status = execute_builtin(args);
	if (loop_status != -1)
	{
		return (loop_status);
	}
	while (NULL != args[j])
	{
		if (0 == ft_strcmp(args[j], "|"))
		{
			return (execute_with_pipe(args));
		}
		j++;
	}
	return (execute_without_pipe(args));
}

