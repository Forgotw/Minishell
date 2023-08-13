/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:59:30 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/13 19:34:29 by lsohler          ###   ########.fr       */
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
# define BRACE_ERROR "Minishell doesn't support opened brace.\n"
# define PARSE_ERROR "parse error near "
# define BAD_SUB "bad substitution"
u_int8_t ret_status;

/*STRUCTRES*/
typedef enum e_operators
{
	ERROR = -3,
	WILDCARD,
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
	AMPER,
	Q_MARK,
	DOL,
	DOL_Q_MARK,
	DOL_DOL,
	D_L_REDIR,
	D_R_REDIR,
	AND,
	OR
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
t_token		*expand_var(t_token **head, t_token *token);
/* TEST */
void	print_tokens(t_token *tokens);

#endif