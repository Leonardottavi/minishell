/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:22:48 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 21:05:54 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(int i, t_pipe *data)
{
	if (i > 0)
	{
		if (dup2(data->pipes[i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (i < data->num_pipes)
	{
		if (dup2(data->pipes[i][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

void	wait_for_commands(t_pipe *data)
{
	int	i;

	i = 0;
	while (i++ < data->num_commands)
	{
		wait(NULL);
	}
}

void	initialize_pipes_and_commands(char **args, t_pipe *data)
{
	count_pipes_and_commands(args, data);
}

void	exe_pipe2(t_pipe *data, char **args)
{
	int	i;

	i = 0;
	while (i < data->num_commands)
	{
		exe_pipe(i, data, args);
		i++;
	}
}
