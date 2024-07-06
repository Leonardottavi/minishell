/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:45:24 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 13:10:05 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	execute_without_pipe(char **args)
{
	pid_t	process_id;

	process_id = fork();
	if (-1 == process_id)
	{
		printf("Failed!\n");
		exit(EXIT_FAILURE);
	}
	if (0 == process_id)
	{
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
	}
	else
		wait(NULL);
	return (1);
}
