/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:59:30 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/08 22:21:50 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include "libft.h"

/*STRUCTRES*/
typedef enum e_operators
{
	EMPTY = -2,
	WORD,
	SPACE,
	SEMIC,
	PIPE,
	QUOTE,
	DQUOTE,
	O_BRACE,
	C_BRACE,
	O_PAR,
	C_PAR,
	L_REDIR,
	R_REDIR,
	WILDC,
	AMPER,
	DOL,
	Q_MARK,
	D_L_REDIR,
	D_R_REDIR,
	AND,
	OR,
	O_STATUS
}				t_operators;

typedef struct s_word
{
	int		q_state;
	int		d_q_state;
	int		w_size;
	int		tok_size;
}				t_word;

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_meta
{
	struct s_cmd	*cmd;
	struct s_meta	*next;
}				t_meta;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	int				heredoc;
	int				infile;
	int				outfile;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

/* FUNCTIONS */
t_token	*init_tokens(char *str);

#endif