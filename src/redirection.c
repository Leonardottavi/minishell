/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:11:06 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/11 14:06:07 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(char **args, int i, int append)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(args[i + 1], flags, 0644);
	if (fd == -1)
	{
		perror("minishell");
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	args[i] = NULL;
}

void	redirect_input(char **args, int i)
{
	while (args[i + 1])
	{
		args[i] = args[i + 1];
		i++;
	}
	args[i] = NULL;
}

void	redirection_ft_control(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], ">") == 0)
			redirect_output(args, i, 0);
		else if (ft_strcmp(args[i], ">>") == 0)
			redirect_output(args, i, 1);
		else if (ft_strcmp(args[i], "<") == 0)
			redirect_input(args, i);
		else if (ft_strncmp(args[i], "<<", 1) == 0
			&& (args[i + 1] || args[i][2]))
			redirect_heredoc(args, i);
		else
		{
			i++;
			continue ;
		}
		break ;
	}
}
