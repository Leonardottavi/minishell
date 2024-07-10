/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:41 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 10:55:57 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_builtin_commands(void)
{
	static char	*builtin_commands[] = {
		"exit", "cd", "help", "pwd",
		"echo", "unset", "env", "export",
	};

	return (builtin_commands);
}

int (*(*get_builtin_functions(void))[])(char **)
{
	static int (*builtin_functions[BUILTIN_COMMANDS + 1])(char**) = {
		&builtin_exit,
		&builtin_cd,
		&builtin_help,
		&builtin_pwd,
		&builtin_echo,
		&builtin_unset,
		&builtin_env,
		&builtin_export,
		&builtin_echo,

	};
return (&builtin_functions);

}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	g_exit_status = 0;
	return (1);
}

int	builtin_help(char **args __attribute__((unused)))
{
	printf("WELCOME ON LOTTAVI & SIMONE MINISHELL HELP COMMAND FAGOTTINO MIO\n");
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
