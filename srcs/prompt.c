/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:14:47 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 18:50:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	salopeva(int x)
// {
// 	if (x == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		write(STDERR_FILENO, "\n", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	else 
// 		printf("tié un chien");
// }

static void	handle_sigint(void)
{

	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigquit(void)
{
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		handle_sigint();
	else if (sig == SIGQUIT)
		handle_sigquit();
}

int	signal_setup(void)
{
	struct sigaction	sig;
	struct termios		tp;

	sig.sa_handler = &signal_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	if (tcgetattr(STDIN_FILENO, &tp) == -1)
		return (-1);
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
		return (-1);
	return (0);
}

int	prompt(char **envp)
{
	char	*input;
	t_token *tokens;
	t_cmd	*ast;
	t_shell	*shell;

	shell = init_shell_data(envp);
	if (signal_setup())
		return (-1);
	while (1)
	{
		// signal(SIGINT, &salopeva);
		input = readline("Minishell$ ");
		if (!input)
			exit (1);
		else if (input[0] != '\0')
		{
			shell->status = TRUE;
			tokens = init_tokens(input);
			// printf("NEW       TOKEN      TYPE\n");
			//print_tokens(tokens);
			syntax_checker(tokens);
			ast = create_ast(tokens, shell);
			//printf("AST DONE %p!\n", ast);
			//executor_print(ast);
			executor(ast);
			// while (wpid > 0)
			// 	wpid = wait(&status);
			free_token(tokens);
			ast_free(ast);
			add_history(input);
		}
	}
	printf("after while(1)\n");
	exit (1);
}