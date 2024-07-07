/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:41 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/07 19:07:13 by lottavi          ###   ########.fr       */
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

void print_arg(char *arg)
{
	if ((arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
		|| (arg[0] == '\"' && arg[ft_strlen(arg) - 1] == '\"'))
	{
		arg[ft_strlen(arg) - 1] = '\0';
		printf("%s", arg + 1);
	}
	else
		printf("%s", arg);
}

int builtin_echo(char **args)
{
	int i = 1;
	int newline = 1;
	int inQuotes = 0;

	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i] != NULL)
	{
		if (args[i][0] == '\'' || args[i][0] == '\"')
		{
			inQuotes = !inQuotes;
			print_arg(args[i]);
		}
		else if (inQuotes)
			printf("%s", args[i]);
		else
		{
			if (ft_strcmp(args[i], "|") == 0 && !inQuotes)
				break;
			print_arg(args[i]);
		}
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	free(args);
	return 1;
}
