/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:21:14 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/23 20:15:47 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
t_token	*expand_dol_dol(t_token *token)
{
	token->type = WORD;
	free(token->str);
	token->str = ft_itoa(getpid());
	return (token);
}

t_token	*expand_dol_q_mark(t_token *token)
{
	token->type = EXP_WORD;
	free(token->str);
	token->str = ft_itoa(ret_status);
	return (token);
}

t_token	*expand_braced_word(t_token **head, t_token *token)
{
	char	*new;
	int		brace_state;

	new = NULL;
	brace_state = 1;
	del_token(head, &token);
	while (token && brace_state)
	{
		if (token->type == C_BRACE)
			brace_state = 0;
		else if (token->type != WORD)
			exit(printf("%s\n", BAD_SUB));
		else
		{
			new = ft_strjoin(new, token->str);
			del_token(head, &token);
		}
	}
	if (!token && brace_state > 0)
		exit(printf("%s", BRACE_ERROR));
	token->type = EXP_WORD;
	free(token->str);
	token->str = new;
	return (token);
}

t_token	*expand_word(t_token **head, t_token *token)
{
	char	*new;

	del_token(head, &token);
	if (token->type == O_BRACE)
		token = expand_braced_word(head, token);
	new = ft_strjoin(token->str, "<TO BE EXPANDED>");
	token->str = new;
	token->type = WORD;
	return (token);
}

t_token	*expand_var(t_token **head, t_token *token)
{
	if (!token)
		return (NULL);
	if (!token->next)
		token->type = WORD;
	else
	{
		if (token->type == DOL_Q_MARK)
			token = expand_dol_q_mark(token);
		else if (token->type == DOL_DOL)
			token = expand_dol_dol(token);
		else if (token->type == DOL && token->next)
		{
			if (token->next->type == WORD || token->next->type == O_BRACE)
				token = expand_word(head, token);
			else
				token->type = WORD;
		}
	}
	return (token);
}
*/
t_token	*token_join_brace(t_token **head, t_token *token)
{
	char	*new;
	int		brace_state;

	new = NULL;
	brace_state = 1;
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
		exit(printf("%s", BRACE_ERROR));
	token->type = EXP_WORD;
	free(token->str);
	token->str = new;
	return (token);
}
t_token	*token_dol_join(t_token **head, t_token *token)
{
	char	*new;
	new = ft_strjoin(ft_strdup(token->str), token->next->str);
	del_token(head, &token);
	free(token->str);
	token->str = new;
	token->type = EXP_WORD;
	printf("New token: str: %s type: %i\n", token->str, token->type);
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
	// printf("New token: str: %s type: %i\n", token->str, token->type);
	token = token->next;
	return (token);
}

/*

t_token	*expand_var(t_token **head, t_token *token)
{
	if (!token->next)
		token->type = WORD;
	else
	{
		if (token->type == DOL_Q_MARK)
			token = expand_dol_q_mark(token);
		else if (token->type == DOL_DOL)
			token = expand_dol_dol(token);
		else if (token->type == DOL && token->next)
		{
			if (token->next == WORD || token->next == O_BRACE)
				token = expand_word(head, token);
			else
				token->type == WORD;
		}
	}
	return (token);
}*/