/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:41 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 17:06:38 by lottavi          ###   ########.fr       */
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
	static int (*builtin_functions[BUILTIN_COMMANDS])(char**) = {
		&builtin_exit,
		&builtin_cd,
		&builtin_help,
		&builtin_pwd,
		&builtin_echo,
		&builtin_unset,
		&builtin_env,
		&builtin_export,
	};
return (&builtin_functions);

}

void	print_arg(char *arg)
{
	if (arg[0] == '\'' || arg[0] == '\"')
	{
		arg[strlen(arg) - 1] = '\0';
		printf("%s", arg + 1);
	}
	else
		printf("%s", arg);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (args[1] && strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i] != NULL)
	{
		if (strcmp(args[i], "|") == 0)
			break ;
		print_arg(args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (1);
}
