/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:00:36 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/04 18:17:47 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void (*(*install_signal_handlers(void))[])(int)
{
	static void (*signal_handlers[SIGNALS])(int) = {
		sigint_handler,
		sigquit_handler,
		sigterm_handler,
	};

	int i = 0;
	while (i < SIGNALS) {
		signal(i + 1, signal_handlers[i]);
		i++;
	}

	return &signal_handlers;
}

char **get_signal(void)
{
	static char *signal_commands[] = {
		"SIGINT", "SIGQUIT", "SIGTERM"
	};

	return signal_commands;
}

void sigint_handler(int signum __attribute__((unused)))
{
	signal(SIGINT, sigint_handler); // Reinstall the handler
	printf("\n");
	printf("minishell> ");
	fflush(stdout); // Ensure the prompt is printed immediately
}

void sigquit_handler(int signum __attribute__((unused)))
{
	signal(SIGQUIT, sigquit_handler); // Reinstall the handler
	printf("\n");
	printf("minishell> ");
	fflush(stdout); // Ensure the prompt is printed immediately
}

void sigterm_handler(int signum __attribute__((unused)))
{
	signal(SIGTERM, sigterm_handler); // Reinstall the handler
	printf("\n");
	printf("minishell> ");
	fflush(stdout); // Ensure the prompt is printed immediately
}


