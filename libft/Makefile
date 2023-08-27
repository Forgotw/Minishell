# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/27 12:53:01 by lsohler           #+#    #+#              #
#    Updated: 2023/08/27 13:03:03 by lsohler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= libft.a
ft_isalpha.c ft_memcmp.c ft_putendl_fd.c ft_striteri.c ft_strncmp.c ft_toupper.c ft_isascii.c\
				ft_memcpy.c ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c ft_atoi.c ft_isdigit.c ft_memmove.c ft_putstr_fd.c\
				ft_strlcat.c ft_strrchr.c ft_bzero.c ft_isprint.c ft_memset.c ft_split.c ft_strlcpy.c ft_strtrim.c ft_calloc.c\
				ft_itoa.c ft_putchar_fd.c ft_strchr.c ft_strlen.c ft_substr.c ft_isalnum.c ft_memchr.c ft_strdup.c ft_strmapi.c ft_tolower.c\
				ft_strndup.c ft_realloc.c ft_arrlen.c array_add_str.c ft_arrdup.c free_array.c
SRCS		= \
			array/array_add_str.c\
			array/free_array.c\
			array/ft_arrdup.c\
			array/ft_arrlen.c\
			array/ft_arrsort.c\
			\
			char/ft_isalnum.c\
			char/ft_isalpha.c\
			char/ft_isascii.c\
			char/ft_isdigit.c\
			char/ft_isprint.c\
			char/ft_tolower.c\
			char/ft_toupper.c\
			\
			list/ft_lstadd_back_bonus.c\
			list/ft_lstadd_front_bonus.c\
			list/ft_lstclear_bonus.c\
			list/ft_lstdelone_bonus.c\
			list/ft_lstiter_bonus.c\
			list/ft_lstlast_bonus.c\
			list/ft_lstmap_bonus.c\
			list/ft_lstnew_bonus.c\
			list/ft_lstsize_bonus.c\
			\
			mem/ft_bzero.c\
			mem/ft_calloc.c\
			mem/ft_memchr.c\
			mem/ft_memcmp.c\
			mem/ft_memcpy.c\
			mem/ft_memmove.c\
			mem/ft_memset.c\
			mem/ft_realloc.c\
			\
			print/ft_putchar_fd.c\
			print/
			print/
			print/

	ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c\
				ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c

OBJS	= $(SRCS:.c=.o)


CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -I.

RM		= rm -f

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: 		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:		
			$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY: all clean fclean re

