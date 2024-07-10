/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:54:27 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 10:56:16 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **args __attribute__((unused)))
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		g_exit_status = 0;
		free(cwd);
	}
	else
	{
		perror("mini-shell");
		g_exit_status = 1;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	if (args[1] != NULL)
	{
		printf("stai cercando di uscire o di ballare la samba?\n");
		g_exit_status = 1;
		return (1);
	}
	else
	{
		free_env(args);
		exit(g_exit_status);
	}
	return (0);
}

char	*format_path(char **args)
{
	char	*path;
	int		path_len;

	if (NULL == args[1])
	{
		printf("mini-shell:\tplease provide the new directory\n");
		g_exit_status = 1;
		return (NULL);
	}
	else
	{
		path = args[1];
		path_len = ft_strlen(path);
		if ((path[0] == '"' && path[path_len - 1] == '"')
			|| (path[0] == '\'' && path[path_len - 1] == '\''))
		{
			path[path_len - 1] = '\0';
			path++;
		}
		return (path);
	}
}

int	change_directory(char *path)
{
	if (path == NULL)
	{
		return (1);
	}
	if (chdir(path) < 0)
	{
		perror("mini-shell");
		g_exit_status = 1;
	}
	else
	{
		g_exit_status = 0;
	}
	return (1);
}

int	builtin_cd(char **args)
{
	char	*path;

	path = format_path(args);
	return (change_directory(path));
}
