/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:41 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/08 13:49:25 by lottavi          ###   ########.fr       */
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
	int i = 1;
	int newline = 1;

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

	g_exit_status = 0; // Set exit status to 0 on successful execution
	return 1;
}
