/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:38:25 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/01 17:02:27 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(char *buffer)
{
	buffer = readline("minishell>");
	return (buffer);
}

void	save_history(char *input)
{
	FILE	*history;

	ft_strcat(ft_strcpy(g_path, getenv("HOME")), "/.history.txt");
	history = fopen(g_path, "a");
	fprintf(history, "%s", input);
	fclose(history);
}
