/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:40:28 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 18:29:31 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Si la combinaison du token et du next token est dans le dictionnaire */
/* On join les deux, on free et le token devient la combinaison */
t_token	*try_join_token(t_token **head, t_token *token, t_word *word)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strjoin(ft_strdup(token->str), token->next->str);
	while (word->sep[i])
	{
		if (!ft_strncmp(word->sep[i], new, ft_strlen(new)))
		{
			del_token(head, &token);
			free(token->str);
			token->str = new;
			token->type = i;
			return (token);
		}
		i++;
	}
	free(new);
	token = token->next;
	return (token);
}

/* Join les words qui se suivent */
t_token	*join_word(t_token **head, t_token *token)
{
	char	*new;
	int		new_type;

	new = NULL;
	new_type = token->type;
	while (token->next && token->next->type <= WORD)
	{
		if (token->type == WILDCARD)
			new_type = WILDCARD;
		else if (token->type == EXP_WORD)
			new_type = EXP_WORD;
		new = ft_strjoin(new, token->str);
		del_token(head, &token);
	}
	new = ft_strjoin(new, token->str);
	token->type = new_type;
	if (token->str)
		free(token->str);
	token->str = new;
	return (token);
}

void	token_join_space(t_token **head, t_token *token)
{
	while (token)
	{
		if (token->type <= WORD && token->next && token->next->type <= WORD)
		{
			token->join = 1;
			token = token->next;
		}
		else if (token->type == SPACE)
			del_token(head, &token);
		else
			token = token->next;
	}
}

/* Apres des quotes, join les words, si DQUOTE expand les var */
/* Expand les vars non quoted */
/* Supprime les tokens espaces */
/* Try join tokens par rapport au dictionnaire */
/* Checker la validité de la liste */
void	token_refiner(t_token **head, t_word *word)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (token->type == QUOTE || token->type == DQUOTE)
			token = join_quoted_token(head, token, word);
		else if (token->type == DOL)
			token = token_dol_type(head, token);
		else if (token->type == Q_MARK)
			token->type = WORD;
		else if (token->type > SPACE && token->next)
			token = try_join_token(head, token, word);
		else if (token)
			token = token->next;
	}
	if (*head && head)
		token_join_space(head, *head);
}
