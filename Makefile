# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 12:31:06 by lsohler           #+#    #+#              #
#    Updated: 2023/09/10 11:11:05 by lsohler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PROJET #
NAME = minishell

# HEADER #
INCLUDES = includes/
HEADER_SRCS = minishell.h
HEADER = $(addprefix $(INCLUDES), $(HEADER_SRCS))
READLINE_DIR := /opt/homebrew/opt/readline

# SOURCES #
SRCS_F = lexer.c main.c parser.c
SRCS_DIR = srcs/ 
SRCS_2 = $(addprefix $(SRCS_DIR), $(SRCS_F))
SRCS = \
		srcs/main.c\
		srcs/executor_print.c\
		srcs/free.c\
		srcs/prompt.c\
		\
		srcs/ast/ast.c\
		srcs/ast/cmd.c\
		srcs/ast/subshell.c\
		srcs/ast/shell.c\
		\
		srcs/builtin/echo.c\
		srcs/builtin/cd.c\
		srcs/builtin/pwd.c\
		srcs/builtin/export.c\
		srcs/builtin/unset.c\
		srcs/builtin/env.c\
		srcs/builtin/exit.c\
		srcs/builtin/builtin.c\
		srcs/builtin/fork.c\
		\
		srcs/exec/bool.c\
		srcs/exec/executor.c\
		srcs/exec/path.c\
		srcs/exec/pipe.c\
		srcs/exec/redir.c\
		\
		srcs/expand/expander.c\
		srcs/expand/wildcard.c\
		\
		srcs/parse/checker.c\
		srcs/parse/lexer.c\
		srcs/parse/operator.c\
		srcs/parse/parser.c\
		srcs/parse/token.c\
		\

OBJS = $(SRCS:.c=.o)

# LIBFT #
LIBFT = libft.a
LIBFT_DIR = libft/
LIBFTS = -L $(LIBFT_DIR) -l ft

# UTILS #
CC = gcc
FLAGS = -Wall -Werror -Wextra
#SANITIZE = -fsanitize=address -g3
RM = rm -rf

# -------  GARDER POUR ECOLE ------- 
LDLIBS		:= -lreadline -L/Users/lsohler/.brew/Cellar/readline/8.2.1/lib/ -I/Users/lsohler/.brew/Cellar/readline/8.2.1/include/readline/
# -------  GARDER POUR MAISON -------
#LDLIBS      := -lreadline -L$(READLINE_DIR)/lib -I $(READLINE_DIR)/include -Wl,-rpath,$(READLINE_DIR)/lib -Llibft -lft

# COLORS #
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
BLUE = \033[0;34m

# COMMANDS #
%.o: %.c
				@$(CC) $(FLAGS) -I $(INCLUDES) -I $(LIBFT_DIR) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
				@
				@$(CC) $(FLAGS) $(SANITIZE) -I $(INCLUDES) $(LIBFTS) $(OBJS) -o $(NAME) ${LDLIBS}
				@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"


all: $(NAME)

norm:
				norminette *.c includes/ libft/

clean:
				@$(RM) $(OBJS)
				@make clean -s -C $(LIBFT_DIR)
				@echo "$(YELLOW)object files cleaned!$(DEFAULT)"

fclean: clean
				@$(RM) $(NAME)
				@$(RM) $(addprefix $(LIBFT_DIR), $(LIBFT))
				@echo "$(RED)$(NAME) cleaned!$(DEFAULT)"

$(LIBFT):	
			@make -s -C $(LIBFT_DIR)
			@echo "$(GREEN)Libft OK !$(DEFAULT)"

re: fclean all

.PHONY:		all clean fclean re
