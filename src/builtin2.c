/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:54:27 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 10:20:44 by lottavi          ###   ########.fr       */
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
		g_exit_status = 1; // Set exit status to 1 on error
		return (1);
	}
	else
	{
		free_env(args);
		exit(g_exit_status); // Exit with the status of the last executed command
	}
	return (0);
}

int	builtin_cd(char **args)
{
	if (NULL == args[1])
	{
		printf("mini-shell:\tplease provide the new directory\n");
		g_exit_status = 1; // Set exit status to 1 on error
	}
	else
	{
		char *path = args[1];
		int path_len = ft_strlen(path);
		if ((path[0] == '"' && path[path_len - 1] == '"')
			|| (path[0] == '\'' && path[path_len - 1] == '\''))
		{
			path[path_len - 1] = '\0';
			path++;
		}
		if (chdir(path) < 0)
		{
			perror("mini-shell");
			g_exit_status = 1; // Set exit status to 1 on error
		}
		else
			g_exit_status = 0; // Set exit status to 0 on successful execution
	}
	return (1);
}

int	builtin_help(char **args __attribute__((unused)))
{
	printf("WELCOME ON LOTTAVI MINISHELL HELP COMMAND FAGOTTINO MIO\n");
	printf("\t-pwd\tfor current directory\n");
	printf("\t-exit\tterminates the shell\n");
	printf("\t-cd\tchanges directory\n");
	printf("\t-echo\tprints the arguments\n");
	printf("\t-unset\tunsets the environment variable\n");
	printf("\t-env\tprints the environment variables\n");
	printf("\t-il resto dei comandi lo fa execve, ma mai bene\n");
	g_exit_status = 0;
	return (1);
}
