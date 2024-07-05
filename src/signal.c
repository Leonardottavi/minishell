/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:00:36 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/05 11:38:59 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum __attribute__((unused))) //ctrlc
{
	signal(SIGINT, sigint_handler); // Reinstall the handler
	printf("\n");
	printf("minishell> ");
}

void	sigquit_handler(int signum __attribute__((unused))) // ctrl"\"
{
	signal(SIGQUIT, SIG_IGN);
	printf("minishell> ");
}
