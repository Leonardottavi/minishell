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

pid_t spawn_proc(int in, int out, char **cmd)
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
	return(pid);
}

int	execute_with_pipe(char **args)
{
	int		i = 0;
	int		in = 0;
	int		fd[2];
	char	**cmd = args;
	pid_t	pid;

	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			args[i] = NULL;
			pipe(fd);
			pid = spawn_proc(in, fd[1], cmd);
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
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execv(cmd_path, cmd);
			free(cmd_path);
			exit(1);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);

			int status;
			waitpid(pid, &status, 0);  /* Wait for the child process to finish */
		}
	}
	else
		printf("Command not found--are you using some kind of weed?\n");
	return 1;
}
