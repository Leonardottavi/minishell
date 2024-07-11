/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:14:23 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/11 14:04:37 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes_and_commands(char **args, t_pipe *data)
{
	int	i;

	i = 0;
	data->pipe_locations[0] = -1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			data->pipe_locations[++(data->num_pipes)] = i;
			args[i] = NULL;
		}
		i++;
	}
	data->num_commands = data->num_pipes + 1;
	return (i);
}

void	close_pipes(t_pipe *data)
{
	int	i;

	i = 0;
	while (i < data->num_pipes)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

void	create_pipes(t_pipe *data)
{
	int	i;

	i = 0;
	while (i < data->num_pipes)
	{
		if (pipe(data->pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	exe_pipe(int i, t_pipe *data, char **args)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_pipe(i, data);
		close_pipes(data);
		cmd_path = get_cmd_path(args[data->pipe_locations[i] + 1]);
		execve(cmd_path, args + data->pipe_locations[i] + 1, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	execute_with_pipe(char **args)
{
	t_pipe	data;

	initialize_pipes_and_commands(args, &data);
	create_pipes(&data);
	exe_pipe2(&data, args);
	close_pipes(&data);
	wait_for_commands(&data);
	return (1);
}
