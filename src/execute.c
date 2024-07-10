/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:20 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 11:54:15 by lottavi          ###   ########.fr       */
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

char	*get_cmd_path_absolute_or_relative(char *cmd)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			return (ft_strdup(cmd));
		}
		else
		{
			return (NULL);
		}
	}
	return (NULL);
}

char	*get_cmd(char *cmd)
{
	char	*path;
	char	*path_copy;
	char	*dir;
	char	*cmd_path;

	path = getenv("PATH");
	path_copy = ft_strdup(path);
	dir = ft_strtok(path_copy, ":");
	while (dir != NULL)
	{
		cmd_path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
		ft_strcpy(cmd_path, dir);
		ft_strcat(cmd_path, "/");
		ft_strcat(cmd_path, cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free(path_copy);
			return (cmd_path);
		}
		free(cmd_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

char	*get_cmd_path(char *cmd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path_absolute_or_relative(cmd);
	if (cmd_path != NULL)
	{
		return (cmd_path);
	}
	return (get_cmd(cmd));
}

int	execute(char **args)
{
	int	j;
	int	loop_status;

	j = 0;
	while (NULL != args[j])
	{
		if (0 == ft_strcmp(args[j], "|"))
		{
			return (execute_with_pipe(args));
		}
		j++;
	}
	loop_status = execute_builtin(args);
	if (loop_status != -1)
	{
		return (loop_status);
	}
	return (execute_without_pipe(args));
}
