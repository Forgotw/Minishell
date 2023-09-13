/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:14:47 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/13 16:49:41 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enter_cmd_line(t_shell *shell)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*ast;

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
			executor(ast);
			free_ast(shell);
		}
	}
}

int	prompt(char **envp)
{
	t_shell	*shell;

	shell = init_shell_data(envp);
	if (signal_setup(0))
		return (-1);
	while (1)
		enter_cmd_line(shell);
	return (0);
}
