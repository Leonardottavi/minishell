/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:00:36 by lottavi           #+#    #+#             */
/*   Updated: 2024/07/05 15:02:43 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum __attribute__((unused))) //ctrlc
{
	rl_replace_line("", 0);
	printf("\nminishell> ");
}

void	sigquit_handler(int signum __attribute__((unused))) // ctrl"\"
{
	exit(0);
}
