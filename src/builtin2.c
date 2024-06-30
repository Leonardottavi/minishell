/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:54:27 by lottavi           #+#    #+#             */
/*   Updated: 2024/06/30 18:36:17 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prints the current working directory
int builtin_pwd(char** args __attribute__((unused)))
{
	char *cwd;
	cwd = getcwd(NULL, 0); // Dynamically allocate buffer size
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		free(cwd); // Free the allocated memory
	}
	else
		perror("mini-shell");
	return 1;
}

// exits out of the mini-shell
int builtin_exit(char** args __attribute__((unused)))
{
	return 0;
}

// changes the current directory
int builtin_cd(char** args)
{
	if (NULL == args[1])	// prints an error message if the user doesn't input the new directory
		printf("mini-shell:\tplease provide the new directory\n");
	else if (chdir(args[1]) < 0)	// changes directory if the new one exists, otherwise prints an error message
		perror("mini-shell");
	return 1;
}

// prints the available built-in commands and a short description for each of them
int builtin_help(char** args __attribute__((unused)))
{
	printf("WELCOME ON LOTTAVI MINISHELL HELP COMMAND FAGOTTINO MIO\n");
	printf("\t-pwd\tfor current directory\n");
	printf("\t-exit\tterminates the shell\n");
	printf("\t-cd\tchanges directory\n");
	printf("\t-echo\tprints the arguments\n");
	printf("\t-unset\tunsets the environment variable\n");
	printf("\t-cat\tprints the contents of the file\n");
	printf("\t-env\tprints the environment variables\n");
	return 1;
}
