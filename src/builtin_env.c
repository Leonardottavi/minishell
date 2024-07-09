/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:06:13 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/08 10:48:00 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_env(char *var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (environ[i] != NULL)
		i++;
	new_env = (char **)malloc((i + 2) * sizeof(char *));
	if (new_env == NULL)
		return (-1);
	j = 0;
	while (j < i)
	{
		new_env[j] = environ[j];
		j++;
	}
	new_env[i] = ft_strdup(var);
	if (new_env[i] == NULL)
		return (-1);
	new_env[i + 1] = NULL;
	environ = new_env;
	return (0);
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

int	remove_from_env(char *var)
{
	int		i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var)) == 0)
		{
			free(environ[i]);
			while (environ[i + 1] != NULL)
			{
				environ[i] = environ[i + 1];
				i++;
			}
			environ[i] = NULL;
			return (0);
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
		printf("mini-shell: unset: not enough arguments\n");
		return (1);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (remove_from_env(args[i]) != 0)
		{
			perror("mini-shell: export");
			return (1);
		}
		i++;
	}
	return (1);
}

int	builtin_env(char **args __attribute__((unused)))
{
	int		i;
	char	**environ_copy;

	i = 0;
	environ_copy = ft_copy_environ(environ);
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
