/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:06:13 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 17:06:42 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strncmp(environ[i], "_=", 2) != 0)
			printf("%s\n", environ[i]);
		i++;
	}
	return (1);
}
