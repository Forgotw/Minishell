/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:14:47 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 19:43:19 by lsohler          ###   ########.fr       */
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

// static void	handle_sigint(void)
// {
// 	fprintf(stdout, "g_status in handle_sigint: %i\n", g_status);
// 	fprintf(stdout, "WIFSIGNALED: %i\n", WIFSIGNALED(g_status));
// 	fprintf(stdout, "WIFEXITED: %i\n", WIFEXITED(g_status));
// 	if (WIFEXITED(g_status))
// 		printf("\n");
// 	else
// 	{
// 		rl_replace_line("", 0);
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	g_status = 1;
// }

// static void	handle_sigquit(void)
// {
// 	rl_on_new_line();
// 	rl_redisplay();
// }

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_status = 1;
}

void	signal_handler_cmd(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		// unlink(".heredoc");
		return ;
	}
}

int	signal_setup(int mode)
{
	struct sigaction	sig;
	struct termios		tp;

	if (mode == 0)
		sig.sa_handler = &signal_handler;
	if (mode == 1)
		sig.sa_handler = &signal_handler_cmd;
	if (mode == 2)
		sig.sa_handler = &signal_handler_heredoc;
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
	t_token	*tokens;
	t_cmd	*ast;
	t_shell	*shell;

	shell = init_shell_data(envp);
	if (signal_setup(0))
		return (-1);
	while (1)
	{
		//input = readline(BLUE "Minishell" RED "$" COLOR_RESET " ");
		input = readline("MiniShell$ ");
		if (!input)
			exit (1);
		else if (input[0] != '\0')
		{
			shell->status = TRUE;
			tokens = init_tokens(input);
			add_history(input);
			free(input);
			if (tokens && !syntax_checker(tokens))
			{
				ast = create_ast(tokens, shell);
				free_token(tokens);
				//executor_print(ast);
				executor(ast);
				free_ast(shell);
			}
			//fprintf(stdout, "g_status end of prompt: %i\n", g_status);
		}
	}
	return (0);
}
