/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:24:50 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/10 18:20:47 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control(char **args, int i)
{
	if (!args[i + 1] && i == 0)
	{
		args[1] = ft_strdup(args[0]);
		free(args[0]);
		args[0] = ft_strdup("echo");
		args[2] = NULL;
	}
	else if (!args[i + 1] && ft_strcmp(args[i - 1], "cat") == 0)
		strcpy(args[i - 1], "echo");
	else
	{
		while (args[i + 1])
		{
			args[i] = args[i + 1];
			i++;
		}
		args[i] = NULL;
	}
}

void	find_comp(char **args, int i, char **comparison)
{
	int	j;

	j = i + 1;
	if (ft_strlen(args[i]) == 2)
	{
		*comparison = strdup(args[i + 1]);
		while (args[j + 1])
		{
			args[j] = args[j + 1];
			j++;
		}
		args[j] = NULL;
	}
	else
		*comparison = strdup(&args[i][2]);
}

void	inwhile(int *j, int i, char *buffer, char **args)
{
	char	*temp;

	if (*j)
	{
		temp = ft_strdup(args[i]);
		free(args[i]);
		args[i] = ft_strjoin(temp, "\n");
		free(temp);
	}
	*j = 1;
	temp = ft_strdup(args[i]);
	free(args[i]);
	args[i] = ft_strjoin(temp, buffer);
	free(temp);
	free(buffer);
	buffer = readline("heredoc> ");
}

void	str_add(int i, char **args, char *str)
{
	char	*temp;

	temp = ft_strdup(args[i]);
	free(args[i]);
	args[i] = ft_strjoin(temp, str);
	free(temp);
}

void	redirect_heredoc(char **args, int i)
{
	char	*buffer;
	char	*comparison;
	int		j;

	find_comp(args, i, &comparison);
	args[i] = ft_strdup("");
	j = 0;
	buffer = readline("heredoc> ");
	while (ft_strcmp(buffer, comparison) != 0)
	{
		if (j)
			str_add(i, args, "\n");
		j = 1;
		str_add(i, args, buffer);
		free(buffer);
		buffer = readline("heredoc> ");
	}
	control(args, i);
	free(comparison);
	free(buffer);
}
