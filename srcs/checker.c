/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:44:46 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/24 14:38:42 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* si parenthese pas fermer PAR_ERROR */
/* si parenthese vide EMPTY_PAR_ERROR */
/* si double pipe ou and ou or */
/*  */
t_token	*join_redir(t_token **head, t_token *token)
{
	if (!token->next || token->next->type > WORD)
		exit (printf("%s %s\n", PARSE_ERROR, token->str));
	else
	{
		token->next->type = token->type;
		del_token(head, &token);
	}
	token = token->next;
	return (token);
}

int	token_checker(t_token **head, t_token *token)
{
	int	par;

	par = 0;
	(void)head;
	while (token)
	{
		if (token->type == O_PAR)
			par++;
		if (token->type == C_PAR)
			par--;
		if (token->type == O_PAR && token->next && token->next->type == C_PAR)
			exit (printf("%s", EMPTY_PAR_ERROR));
	}
	return (0);
}