/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:24:47 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/01 15:19:31 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler()
{
	printf("minishell: killed\n");
	exit(0);
}

void save_history(char* input)
{
	ft_strcat(ft_strcpy(g_path, getenv("HOME")), "/.history.txt");
	FILE* history = fopen(g_path, "a");
	fprintf(history, "%s", input);
	fclose(history);
}

char* get_input(char* buffer)
{
	printf("mini-shell>");
	fgets(buffer, MAX_BUFFER_SIZE, stdin);
	return (buffer);
}

char** get_args(char* input, char** args)
{
	int	i;

	i = 0;
	char* token = strtok(input, " ");
	while (NULL != token)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	int j = 0;
	while (NULL != args[j])
	{
		args[j] = strtok(args[j], "\n");
		j++;
	}
	return (args);
}

int main()
{
	signal(SIGINT, sigint_handler);
	char* input = (char*)malloc(sizeof(char) * MAX_BUFFER_SIZE);
	if (NULL == input)
	{
		perror("malloc");
		return -1;
	}
	char** args_buffer = (char**)malloc(sizeof(char*) * MAX_BUFFER_SIZE);
	if (NULL == args_buffer)
	{
		perror("malloc");
		return -1;
	}
	char** args;
	int loop_status;

	loop_status = 1;
	while(loop_status)
	{
		input = get_input(input);
		if (32 == input[0] || 9 == input[0] || 0 == strcmp(input, "\n") || NULL == input)
			continue;
		 else
		{
			save_history(input);
			args = get_args(input, args_buffer);
			loop_status = execute(args);
		}
	}
	free(input);
	free(args);
	return (0);
}
