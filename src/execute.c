/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:20 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/05 13:57:48 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (-1 == execvp(args[0], args))
			printf("Command not found--are you using some kind of weed?\n");
	}
	else
		wait(NULL);
	return (1);
}

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

int	execute_with_pipe(char **args)
{
	char	*left_side[3];
	char	*right_side[3];
	int		fd[2];
	pid_t	child1;
	pid_t	child2;

	parse_pipe_args(args, left_side, right_side);
	failed_pipe(fd);
	execute_left_side(fd, left_side);
	child1 = fork();
	execute_right_side(fd, right_side);
	child2 = fork();
	close(fd[0]);
	close(fd[1]);
	process_checker(child1, child2);
	return (1);
}
