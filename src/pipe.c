/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:58:58 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 11:31:09 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void spawn_proc(int in, int out, char **cmd)
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		char *cmd_path = get_cmd_path(cmd[0]);
		if (cmd_path != NULL)
		{
			execv(cmd_path, cmd);
			free(cmd_path);
		}
		else
		{
			printf("Command not found--are you using some kind of weed?\n");
		}
		exit(1);
	}
}

int	execute_with_pipe(char **args)
{
	int i = 0;
	int in = 0;
	int fd[2];
	char **cmd = args;

	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			args[i] = NULL;
			pipe(fd);
			spawn_proc(in, fd[1], cmd);
			close(fd[1]);
			in = fd[0];
			cmd = args + i + 1;
		}
		i++;
	}
	if (in != 0)
		dup2(in, 0);
	char *cmd_path = get_cmd_path(cmd[0]);
	if (cmd_path != NULL)
	{
		execv(cmd_path, cmd);
		free(cmd_path);
	}
	else
	{
		printf("Command not found--are you using some kind of weed?\n");
	}
	return 1;
}
