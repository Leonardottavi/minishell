/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:06:13 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 18:21:23 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_to_env(char *var)
{
	int i = 0;
	while (environ[i] != NULL)
		i++;
	char **new_env = realloc(environ, (i + 2) * sizeof(char *));
	if (new_env == NULL)
		return -1;
	new_env[i] = strdup(var);
	if (new_env[i] == NULL)
		return -1;
	new_env[i + 1] = NULL;
	environ = new_env;
	return 0;
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
		if (add_to_env(args[i]) != 0)
		{
			perror("mini-shell: export");
			return (1);
		}
		i++;
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

int builtin_env(char **args __attribute__((unused)))
{
	int i = 0;
	char **environ_copy = ft_copy_environ(environ);
	if (environ_copy == NULL)
	{
		printf("Environment not initialized.\n");
		return (1);
	}

	while (environ_copy[i] != NULL)
	{
		if (ft_strncmp(environ_copy[i], "_=", 2) != 0)
			printf("%s\n", environ_copy[i]);
		i++;
	}
	free_environ_copy(environ_copy);
	return (1);
}
