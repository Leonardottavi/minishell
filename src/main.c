/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:09:37 by lottavi           #+#    #+#             */
/*   Updated: 2024/02/07 16:05:28 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	acces(char *path)
{
	if (access(path, F_OK) == -1)
	{
		printf("%s: %s: %s\n",GREEN, path, RESET);
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		printf("%s: %s: %s\n",RED, path, RESET);
		return (0);
	}
}

int	execve(char *path, char **av, char **env)
{
	if (acces(path) == 0)
		return (0);
	if (execve(path, av, env) == -1)
	{
		printf("%s: %s: %s\n",RED, path, RESET);
		return (0);
	}
}

int	main(int ac, char **av, char **env)
{

}
