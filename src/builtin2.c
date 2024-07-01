/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:54:27 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/01 15:32:20 by lottavi          ###   ########.fr       */
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
		free(cwd);
	}
	else
		perror("mini-shell");
	return (1);
}

int	builtin_exit(char **args __attribute__((unused)))
{
	return (0);
}

int	builtin_cd(char **args)
{
	if (NULL == args[1])
		printf("mini-shell:\tplease provide the new directory\n");
	else if (chdir(args[1]) < 0)
		perror("mini-shell");
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
	return (1);
}

int	builtin_export(char **args)
{
	int	i;

	if (args[1] == NULL)
	{
		printf("mini-shell: export: not enough arguments\n");
		return (1);
	}
	i = 1;
	while (args[i] != NULL)
	{
		i++;
	}
	if (putenv(args[i]) != 0)
	{
		perror("mini-shell: export");
		return (1);
	}
	return (1);
}