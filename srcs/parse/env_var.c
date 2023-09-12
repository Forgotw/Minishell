/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:36:12 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 18:39:08 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_join_brace(t_token **head, t_token *token)
{
	char	*new;
	int		brace_state;

	new = NULL;
	brace_state = 1;
	del_token(head, &token);
	del_token(head, &token);
	while (token && brace_state)
	{
		if (token->type == C_BRACE)
			brace_state = 0;
		else
		{
			new = ft_strjoin(new, token->str);
			del_token(head, &token);
		}
	}
	if (!token && brace_state > 0)
		return (quote_error(head, O_BRACE));
	token->type = EXP_WORD;
	free(token->str);
	token->str = new;
	return (token);
}

t_token	*token_dol_join(t_token **head, t_token *token)
{
	del_token(head, &token);
	token->type = EXP_WORD;
	return (token);
}

t_token	*token_dol_type(t_token **head, t_token *token)
{
	if (!token->next || token->next->type == SPACE)
		token->type = WORD;
	else if (token->next->type == Q_MARK || token->next->type == DOL
		|| token->next->type == WORD)
		token = token_dol_join(head, token);
	else if (token->next->type == O_BRACE)
		token = token_join_brace(head, token);
	if (token)
		token = token->next;
	return (token);
}
