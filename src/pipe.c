/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:58:58 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/05 17:38:22 by lottavi          ###   ########.fr       */
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
		execvp(cmd[0], cmd);
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
	execvp(cmd[0], cmd);
	return 1;
}
