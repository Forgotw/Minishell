/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:18:05 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 18:30:38 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*quote_error(t_token **head, int type)
{
	free_token(*head);
	if (type == QUOTE || type == DQUOTE)
		ft_putstr_fd(QUOTE_ERROR, 2);
	if (type == O_BRACE)
		ft_putstr_fd(BRACE_ERROR, 2);
	ret_status = 1;
	*head = NULL;
	return (NULL);
}

t_token	*empty_word_token(t_token *token)
{
	token->type = WORD;
	free(token->str);
	token->str = ft_strdup("\0");
	token = token->next;
	return (token);
}

/* Si on trouve un token quote ou dquote */
/* Tant qu'on trouve pas ce token exact */
/* On join les tokens en fonction du type de quote */
/* On expand si dquote et token $ */
t_token	*join_quoted_token(t_token **head, t_token *token, t_word *word)
{
	word->q_state = token->type;
	del_token(head, &token);
	if (token->type == word->q_state)
		return (empty_word_token(token));
	while (token && word->q_state > 0)
	{
		if (token->type == word->q_state)
			word->q_state = 0;
		else
		{
			if (token->type == DOL && word->q_state == DQUOTE)
				token = token_dol_type(head, token);
			else
			{
				token->type = WORD;
				token = token->next;
			}
		}
	}
	if (!token && word->q_state > 0)
		return (quote_error(head, word->q_state));
	del_token(head, &token);
	return (token);
}