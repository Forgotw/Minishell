/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:40:28 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/09 17:57:13 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_next_token(t_token **token)
{
	t_token	*tmp;

	tmp = (*token);
	if ((*token)->next)
	{
		(*token)->next = (*token)->next->next;
		(*token)->next->prev = (*token);
	}
	if (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	del_token(t_token **token)
{
	t_token	*tmp;

	tmp = (*token);
	if ((*token)->next)
	{
		(*token)->next->prev = (*token)->prev;
		(*token) = (*token)->next;
	}
	if (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	join_quoted_token(t_token *token, t_word *word)
{
	char	*new;

	new = NULL;
	word->q_state = 1;
	word->q_id = token->type;
	while (word->q_state == 1)
	{
		if (token->type == DOL)
			expend_var(token);
		new = ft_strjoin(new, token->str);
	}
}

int	try_join_token(t_token *token, t_word *word)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strjoin(token->str, token->next->str);
	while (word->sep[i])
	{
		if (!ft_strncmp(word->sep[i], new, ft_strlen(new)))
		{
			del_next_token(&token);
			token->str = new;
			token->type = word->sep[i];
			return (0);
		}
	}
	free(new);
	printf("%s%s\n", PARSE_ERROR, token->next->str);
	return (1);
}

void	token_refiner(t_token *token, t_word *word)
{
	while (token)
	{
		if (token->type == QUOTE || token->type == DQUOTE)
			join_quoted_token(token, word);
		else if (token->next->type != WORD && token->next->type != SPACE
			&& token->next->type != QUOTE && token->next->type != DQUOTE)
			try_join_token(token, word);
		token = token->next;
	}
}
