/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:36:02 by lottavi           #+#    #+#             */
/*   Updated: 2024/06/30 17:36:28 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_command_line(char** args, char** left_side, char** right_side) {
	int i = 0, j = 0;
	while (0 != strcmp(args[i], "|")) {
		left_side[i] = args[i];
		i++;
	}
	left_side[i] = NULL;
	i++;
	while (args[i] != NULL) {
		right_side[j] = args[i];
		i++;
		j++;
	}
	right_side[j] = NULL;
}

void execute_left_command(char** left_side, int* fd) {
	if (-1 == execvp(left_side[0], left_side)) {
		printf("Command not found--Did you mean something else?\n");
		exit(1);
	}
}

void execute_right_command(char** right_side, int* fd) {
	if (-1 == execvp(right_side[0], right_side)) {
		printf("Command not found--Did you mean something else?\n");
		exit(1);
	}
}
// executes terminal built-in commands by feeding the output of the first command into the input of the second command
#int execute_with_pipe(char** args) {
    char* left_side[3];
    char* right_side[3];
    parse_command_line(args, left_side, right_side);

    int fd[2];
    if (-1 == pipe(fd)) {
        printf("Piping failed for some reason!\n");
        exit(EXIT_FAILURE);
    }
    pid_t child_process_id = fork();
    if (-1 == child_process_id) {
        printf("Fork failed for some reason!\n");
        exit(EXIT_FAILURE);
    } else if (0 == child_process_id) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execute_left_command(left_side, fd);
    }
    pid_t child_process_id2 = fork();
    if (-1 == child_process_id2) {
        printf("Fork failed for some reason!\n");
        exit(EXIT_FAILURE);
    } else if (0 == child_process_id2) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execute_right_command(right_side, fd);
    } else {
        close(fd[0]);
        close(fd[1]);
        int child_status;
        waitpid(child_process_id, &child_status, 0);
        int child_status2;
        waitpid(child_process_id2, &child_status2, 0);
    }
    return 1;
}
