/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:59:30 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/02 15:05:14 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft.h"

# define QUOTE_ERROR "Minishell doesn't support opened quote.\n"
# define BRACE_ERROR "Minishell doesn't support opened brace.\n"
# define PAR_ERROR "Minishell doesn't support opened parenthesis.\n"
# define LINK_ERROR "Minishell doesn't support opened link.\n"
# define EMPTY_PAR_ERROR "Minishell doesn't support empty parenthesis.\n"
# define PARSE_ERROR "Minishell: syntax error near unexpected token: "
# define CMD_ENV_ERROR "Minishell doesn't support env parameters"
# define BAD_SUB "bad substitution"
# define NO_MATCHES "no matches found:"
# define BAD_IDENTIFIER ": not a valid identifier\n"
# define STDIN 0
# define STDOUT 1
# define STDERR 2

u_int8_t ret_status;

/*STRUCTRES*/
typedef enum e_operators
{
	ERROR = -4,
	WILDCARD,
	EXP_WORD,
	WORD,
	SPACE,
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
	OR,
	SUBSHELL,
	CMD
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
	int				join;
	int				redir;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_dtok
{
	struct s_token	*start;
	struct s_token	*end;
}				t_dtok;

typedef struct s_meta
{
	struct s_cmd	*cmd;
	struct s_meta	*next;
}				t_meta;

typedef struct s_wildcard
{
	char			**find_arr;
	char			currentdir[1024];
	char			*find;
	char			*buff;
	DIR				*dir;
	struct dirent	*entry;
}				t_wildcard;

typedef struct s_cmd
{
	int				type;
	int				linktype;
	int				redirtype;
	char			**cmd;
	char			*path;
	int				heredoc;
	int				infile;
	int				outfile;
	pid_t			pid;
	struct s_token	*tok;
	struct s_token	*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_cmd	*subshell;
	struct s_cmd	*upshell;
	struct s_shell	*shell;
}				t_cmd;

typedef struct s_shell
{
	char		**env;
	char		path[1024];
	char		oldpath[1024];
	char		homepath[1024];
	int			status;
	t_cmd		*ast;
}				t_shell;

/*   FUNCTIONS   */
/* TOKEN UTILS */
void		del_token(t_token **head, t_token **token);
void		token_add_back(t_token **redir, t_token *new);
t_token		*new_tok(t_token *token, char *str, int type);
t_token		*token_dup(t_token *token);
t_token		*new_word(t_token *token, char *buff);
/* FREE UTILS */
void		free_token(t_token *token);
int			ast_free(t_cmd *ast);
/* PARSING */
t_token		*init_tokens(char *str);
const char	**init_sep(void);
void		token_refiner(t_token **token, t_word *word);
void		syntax_checker(t_token *token);
char		**create_cmd_array(t_token *token);
/* EXPANDER */
t_token		*expand_token(t_token *token, t_shell *shell);
t_token		*token_dol_type(t_token **head, t_token *token);
t_token		*expand_var(t_token **head, t_token *token, t_shell *shell);
t_token		*expand_wildcard(t_token **head, t_token *token);
t_token		*expand_return(t_token *token, t_shell *shell);
/* AST */
t_cmd		*create_ast(t_token *token, char **envp);
t_cmd		*create_subshell(t_token **token, t_cmd *ast, t_shell *shell);
t_cmd		*close_subshell(t_token **token, t_cmd *ast);
t_cmd		*new_cmd(int cmdtype, t_shell *shell);
t_shell		*init_shell_data(char **envp);
char		**create_cmd_array(t_token *token);
/* REDIR */
t_token		*join_redir_token(t_token *token);
int			assign_redir(t_token *token, t_cmd *node);
/* TEST */
int			executor_print(t_cmd *ast);
void		print_tokens(t_token *tokens);
void		print_array(char **array);
void		print_cmd(t_cmd *ast, char *indent);
int			print_export(char **env);
/* BUILTIN */
int			export(char **cmd, t_shell *shell);
int			unset(char	**cmd, t_shell *shell);
int			var_identifier_error(char *str, char *cmd);
int			my_execve(t_cmd *node, int *status);
int			prompt(char **envp);

#endif