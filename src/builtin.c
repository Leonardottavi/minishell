/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:41 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/01 12:14:03 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	g_path[1024];

char **get_builtin_commands()
{
	static char *builtin_commands[] = {
		"exit", "cd", "help", "pwd", "echo", "unset", "env", NULL
	};
	return (builtin_commands);
}

int		(*g_builtin_functions[BUILTIN_COMMANDS])(char**) = {
	&builtin_exit,
	&builtin_cd,
	&builtin_help,
	&builtin_pwd,
	&builtin_echo,
	&builtin_unset,
	&builtin_env,
};

int	builtin_unset(char **args)
{
	int	i;

	if (args[1] == NULL)
	{
		printf("mini-shell: unset: a variable name is required\n");
		return (1);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_unsetenv(args[i]) != 0)
			perror("mini-shell");
		i++;
	}
	return (1);
}

int	builtin_env(char **args __attribute__((unused)))
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (args[1] && strcmp(args[1], "-n") == 0) {
		newline = 0; // Do not print the newline
		i = 2; // Start printing from the next argument
	}

	while (args[i] != NULL) {
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");

	return (1);
}
