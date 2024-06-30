/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:22:41 by lottavi           #+#    #+#             */
/*   Updated: 2024/06/30 20:13:04 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	g_path[1024];
char	*g_builtin_commands[] =
{
	"exit", "cd", "help",
	"pwd", "echo", "unset", "cat", "env"
};

int	(*g_builtin_functions[BUILTIN_COMMANDS])(char**) =
{
	&builtin_exit,
	&builtin_cd,
	&builtin_help,
	&builtin_pwd,
	&builtin_echo,
	&builtin_unset,
	&builtin_cat,
	&builtin_env
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

int	builtin_cat(char **args)
{
	int		i;
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;

	i = 1;
	while (args[i] != NULL)
	{
		fd = open(args[i], O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening file");
			i++;
			continue ;
		}
		while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytes_read] = '\0';
			printf("%s", buffer);
		}
		close(fd);
		i++;
	}
	return (1);
}

int	builtin_echo(char**args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
	return (1);
}
