# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 12:31:06 by lsohler           #+#    #+#              #
#    Updated: 2023/08/22 20:37:52 by lsohler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PROJET #
NAME = minishell

# HEADER #
INCLUDES = includes/
HEADER_SRCS = minishell.h
HEADER = $(addprefix $(INCLUDES), $(HEADER_SRCS))

# SOURCES #
SRCS_F = lexer.c main.c parser.c
SRCS_DIR = srcs/ 
SRCS_2 = $(addprefix $(SRCS_DIR), $(SRCS_F))
SRCS = srcs/lexer.c srcs/main.c srcs/parser.c srcs/operator.c srcs/expander.c srcs/wildcard.c srcs/ast.c srcs/executor.c
OBJS = $(SRCS:.c=.o)

# LIBFT #
LIBFT = libft.a
LIBFT_DIR = libft/
LIBFTS = -L $(LIBFT_DIR) -l ft

# UTILS #
CC = gcc
FLAGS = -Wall -Werror -Wextra
SANITIZE = -fsanitize=address -g3
SANITIZETHREAD = -fsanitize=thread -g3
RM = rm -rf

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
				@$(CC) $(FLAGS) -I $(INCLUDES) $(LIBFTS) $(OBJS) -o $(NAME)
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