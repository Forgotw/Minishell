/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:09:36 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 20:37:30 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_write(t_token *token, int file)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line)
			return (-1);
		if (!ft_strncmp(token->str, line, ft_strlen(token->str) + 1))
		{
			free(line);
			break ;
		}
		write (file, line, ft_strlen(line));
		write (file, "\n", 1);
		free(line);
	}
	return (0);
}

int	here_doc(t_cmd *node, t_token *token)
{
	int		file;

	signal_setup(2);
	unlink(".heredoc");
	file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return (-1);
	here_doc_write(token, file);
	close(file);
	node->infile = open (".heredoc", O_RDONLY);
	signal_setup(0);
	if (node->infile < 0)
	{
		unlink(".heredoc");
		node->infile = 0;
		return (-1);
	}
	return (0);
}

int	open_error(char *filename)
{
	ft_putstr_fd("Minishell: ", 2);
	perror(filename);
	return (-1);
}

int	assign_redir(t_token *token, t_cmd *node)
{
	while (token)
	{
		if (token->redir == D_L_REDIR)
			here_doc(node, token);
		else if (token->redir == L_REDIR)
			node->infile = open(token->str, O_RDONLY);
		else if (token->redir == R_REDIR)
			node->outfile = open(token->str,
					O_CREAT | O_RDWR | O_TRUNC, 0777);
		else if (token->redir == D_R_REDIR)
			node->outfile = open(token->str,
					O_CREAT | O_RDWR | O_APPEND, 0777);
		if (node->infile < 0 || node->outfile < 0)
			return (open_error(token->str));
		else
		{
			if (node->infile)
				fd_collector(&node->shell->fdlist, node->infile);
			if (node->outfile)
				fd_collector(&node->shell->fdlist, node->infile);
		}
		token = token->next;
	}
	return (0);
}

t_token	*join_redir_token(t_token *token)
{
	t_token	*head;
	char	*new;

	head = token;
	new = NULL;
	while (token)
	{
		while (token->join && token->next)
		{
			new = ft_strjoin(new, token->str);
			del_token(&head, &token);
			if (!token->join)
			{
				new = ft_strjoin(new, token->str);
				if (token->str)
					free(token->str);
				token->str = new;
			}
		}
		token = token->next;
	}
	return (head);
}
