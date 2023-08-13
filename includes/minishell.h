/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:59:30 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/13 13:19:39 by lsohler          ###   ########.fr       */
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

# define QUOTE_ERROR "Minishell doesn't support opened quote.\n"
# define PARSE_ERROR "Minishell parse error near "

/*STRUCTRES*/
typedef enum e_operators
{
	ERROR = -2,
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
	R_STATUS,
	TIDLE,
	DOL_Q_MARK,
	DOL_DOL
}				t_operators;

typedef struct s_word
{
	int			q_state;
	int			q_id;
	int			tok_size;
	const char	**sep;
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
t_token		*init_tokens(char *str);
const char	**init_sep(void);
void		token_refiner(t_token **token, t_word *word);
void		del_token(t_token **head, t_token **token);
void		free_array(char **array);
/* TEST */
void	print_tokens(t_token *tokens);

#endif