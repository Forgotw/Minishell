/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:59:30 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 20:36:14 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
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
# define LINK_ERROR "Minishell doesn't support no command after link.\n"
# define EMPTY_PAR_ERROR "Minishell parenthesis error.\n"
# define PARSE_ERROR "Minishell: syntax error near unexpected token: "
# define CMD_ENV_ERROR "Minishell doesn't support env parameters"
# define BAD_SUB "bad substitution"
# define NO_MATCHES "no matches found:"
# define BAD_IDENTIFIER ": not a valid identifier\n"
# define STDIN 0
# define STDOUT 1
# define STDERR 2

int	g_status;

/*COULEURS */

# define BLUE		"\x1b[36m"
# define RED		"\x1b[35m"
# define GREEN	"\x1b[32m"
# define COLOR_RESET	"\x1b[0m"

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
	char				**env;
	char				path[1024];
	char				oldpath[1024];
	int					status;
	int					pipefd[2];
	int					prev_pipe_in;
	struct s_address	*collector;
	struct s_fdlist		*fdlist;
}				t_shell;

typedef struct s_address
{
	void				*address;
	int					type;
	struct s_address	*next;
}				t_address;

typedef struct s_fdlist
{
	int				fd;
	struct s_fdlist	*next;
}				t_fdlist;

/*   FUNCTIONS   */
/* TOKEN */
void		del_token(t_token **head, t_token **token);
void		token_add_back(t_token **redir, t_token *new);
t_token		*new_tok(t_token *token, char *str, int type);
t_token		*token_dup(t_token *token);
t_token		*new_word(t_token *token, char *buff);
t_token		*join_quoted_token(t_token **head, t_token *token, t_word *word);
/* FREE */
void		free_token(t_token *token);
int			ast_free(t_cmd *ast);
void		free_ast(t_shell *shell);
void		ast_address_collector(t_address **collector,
				void *address, int type);
void		fd_collector(t_fdlist **fdlist, int fd);
void		close_all_fd(t_fdlist *fdlsit);
/* PARSING */
t_token		*init_tokens(char *str);
const char	**init_sep(void);
void		token_refiner(t_token **token, t_word *word);
int			syntax_checker(t_token *token);
t_token		*quote_error(t_token **head, int type);
char		**create_cmd_array(t_token *token);
t_token		*token_dol_type(t_token **head, t_token *token);
/* EXPANDER */
t_token		*expand_token(t_token *token, t_shell *shell);
t_token		*expand_var(t_token **head, t_token *token, t_shell *shell);
t_token		*expand_wildcard(t_token **head, t_token *token);
t_token		*expand_return(t_token *token, t_shell *shell);
void		insert_expand(t_token **head, t_token *token, t_dtok *toks);
char		*get_env_variable(char *var, t_shell *shell);
/* AST */
t_cmd		*create_ast(t_token *token, t_shell *shell);
t_cmd		*create_subshell(t_token **token, t_cmd *ast, t_shell *shell);
t_cmd		*close_subshell(t_token **token, t_cmd *ast);
t_cmd		*new_cmd(int cmdtype, t_shell *shell);
t_shell		*init_shell_data(char **envp);
char		**create_cmd_array(t_token *token);
t_cmd		*create_node_on_subshell(int type, t_shell *shell, t_cmd *ast);
t_cmd		*create_node_on_next(int type, t_shell *shell, t_cmd *ast);
/* REDIR */
t_token		*join_redir_token(t_token *token);
int			assign_redir(t_token *token, t_cmd *node);
void		redir_prev_pipe_in(t_cmd *node);
void		redir_child(t_cmd *node);
void		fork_and_pipe(t_cmd *node);
/* EXECUTOR */
int			executor(t_cmd *node);
int			is_builtin(char	*cmd);
int			exec_builtin(char **cmd, t_shell *shell, t_cmd *node);
void		boolean_link(t_cmd *node);
int			execute_cmd(t_cmd *node, int *status);
void		get_g_status(int *status);
t_cmd		*skip_subshell(t_cmd *node);
t_cmd		*nav_cmd(t_cmd *node, int *status);
t_cmd		*nav_subshell(t_cmd *node, int *status);
/* SIGNAL */
int			signal_setup(int mode);
/* TEST */
int			executor_print(t_cmd *ast);
void		print_tokens(t_token *tokens);
void		print_array(char **array);
void		print_cmd(t_cmd *ast, char *indent);
void		print_token_exec(t_token *token, int redir);
int			print_export(char **env);
/* BUILTIN */
int			export(char **cmd, t_shell *shell);
int			unset(char	**cmd, t_shell *shell);
int			var_identifier_error(char *str, char *cmd);
int			my_execve(t_cmd *node);
int			change_directory(char **cmd, t_shell *shell);
int			my_echo(char **cmd, t_shell *shell);
int			my_exit(char **cmd, t_shell *shell);
int			print_working_directory(char **cmd, t_shell *shell);
int			env(char **cmd, t_shell *shell);
int			get_path_type(char **cmd, t_cmd *node);
int			fork_builtin(char **cmd, t_cmd *node, t_shell *shell,
				int (*function)(char **, t_shell *));

int			prompt(char **envp);
extern void	rl_replace_line(const char *str, int i);

#endif