/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:11:06 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/06 17:25:44 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirect_output(char **args, int i, int append)
{
	int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	int fd = open(args[i + 1], flags, 0644);
	if (fd == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	args[i] = NULL;
}

void redirect_input(char **args, int i)
{
	int fd = open(args[i + 1], O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	args[i] = NULL;
}

void redirection_control(char **args)
{
	int i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], ">") == 0)
		{
			redirect_output(args, i, 0);
			break;
		}
		else if (ft_strcmp(args[i], ">>") == 0)
		{
			redirect_output(args, i, 1);
			break;
		}
		else if (ft_strcmp(args[i], "<") == 0)
		{
			redirect_input(args, i);
			break;
		}
		else if (ft_strcmp(args[i], "<<") == 0)
		{
			redirect_heredoc(args, i);
			break;
		}
		i++;
	}
}
