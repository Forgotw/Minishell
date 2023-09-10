/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:23:55 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/25 20:46:34 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token **redir, t_token *new)
{
	t_token	*tmp;

	if (*redir)
	{
		tmp = *redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*redir = new;
}

t_token	*new_word(t_token *token, char *buff)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->type = WORD;
	new->join = 0;
	new->redir = 0;
	new->str = ft_strdup(buff);
	if (buff)
		free(buff);
	new->prev = token;
	new->next = NULL;
	return (new);
}

t_token	*new_tok(t_token *token, char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->type = type;
	new->join = 0;
	new->redir = 0;
	new->str = ft_strdup(str);
	new->prev = token;
	new->next = NULL;
	return (new);
}

t_token	*token_dup(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->type = token->type;
	new->join = token->join;
	new->redir = 0;
	if (token->str)
		new->str = ft_strdup(token->str);
	else
		new->str = ft_strdup("\0");
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

/* Delete le token re-assigne les liaisons et free les malloc */
/* Si le token a remove est la head, on reassigne la head en consequence */
void	del_token(t_token **head, t_token **remove)
{
	t_token	*tmp;

	if (!(*remove)->next)
	{
		if ((*remove)->prev)
			(*remove)->prev->next = NULL;
		if ((*remove)->str)
			free((*remove)->str);
		free(*remove);
		*remove = NULL;
	}
	if (*remove)
	{
		tmp = (*remove)->next;
		if ((*remove)->next)
			(*remove)->next->prev = (*remove)->prev;
		if ((*remove)->prev)
			(*remove)->prev->next = (*remove)->next;
		if ((*remove)->str)
			free((*remove)->str);
		free(*remove);
		*remove = tmp;
		if (!tmp->prev)
			*head = *remove;
	}
}
