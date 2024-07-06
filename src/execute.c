/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:20 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 10:45:12 by lottavi          ###   ########.fr       */
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

