/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:44:46 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 15:02:51 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* si parenthese pas fermer PAR_ERROR */
/* si parenthese vide EMPTY_PAR_ERROR */
/* si double pipe ou and ou or */
/*  */
int	syntax_redir_parsing(t_token *token)
{
	if ((token->type == L_REDIR
			|| token->type == R_REDIR
			|| token->type == D_L_REDIR
			|| token->type == D_R_REDIR)
		&& (!token->next || token->next->type > WORD))
		return (1);
	return (0);
}

int	syntax_par_parsing(t_token *token)
{
	if ((token->type == AND || token->type == OR
			|| token->type == PIPE) && !token->next)
		return (1);
	else if (token->type == O_PAR && token->next
		&& token->next->type == C_PAR)
		return (2);
	return (0);
}

int	syntax_link_parsing(t_token *token)
{
	if ((token->type == AND || token->type == OR || token->type == PIPE)
		&& token->next
		&& (token->next->type == AND || token->next->type == OR
			|| token->next->type == PIPE))
		return (1);
	return (0);
}

int	syntax_parsing(t_token *token)
{
	int	par;

	par = 0;
	while (token)
	{
		if (token->type == O_PAR)
			par++;
		if (token->type == C_PAR)
			par--;
		if (syntax_link_parsing(token))
			return (printf("%s%s\n", PARSE_ERROR, token->str));
		else if (syntax_par_parsing(token) == 1)
			return (printf("%s", LINK_ERROR));
		else if (syntax_par_parsing(token) == 2)
			return (printf("%s", EMPTY_PAR_ERROR));
		else if (syntax_redir_parsing(token))
			return (printf("%s%s\n", PARSE_ERROR, token->str));
		token = token->next;
	}
	if (par)
		return (printf("%s", EMPTY_PAR_ERROR));
	return (0);
}

int	syntax_checker(t_token *token)
{
	if (token->type == AND || token->type == OR
		|| token->type == PIPE)
	{
		printf("%s%s\n", PARSE_ERROR, token->str);
		ret_status = 258;
		free_token(token);
		return (ret_status);
	}
	if (syntax_parsing(token))
	{
		free_token(token);
		ret_status = 258;
		return (ret_status);
	}
	return (0);
}
