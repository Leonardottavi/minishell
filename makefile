# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/29 12:33:15 by lottavi           #+#    #+#              #
#    Updated: 2024/06/30 17:52:19 by lottavi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = build
LIB_DIR = lib
NAME = minishell
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBS = -L$(LIB_DIR) -lft

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

libft:
	make -C $(LIB_DIR)

clean:
	rm -f $(OBJS)
	rm -f $(LIB_DIR)/*.o

fclean: clean
	clean rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
