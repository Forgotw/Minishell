/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:40:28 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/02 14:54:31 by lsohler          ###   ########.fr       */
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
		exit(printf("%s", QUOTE_ERROR));
	del_token(head, &token);
	return (token);
}
// t_token	*join_quoted_token(t_token **head, t_token *token, t_word *word)
// {
// 	char	*new;
// 	int		new_type;

// 	new = NULL;
// 	new_type = WORD;
// 	word->q_state = token->type;
// 	del_token(head, &token);
// 	while (token && word->q_state > 0)
// 	{
// 		if (token->type == word->q_state)
// 			word->q_state = 0;
// 		else
// 		{
// 			if (token->type == DOL && word->q_state == DQUOTE)
// 				new_type = EXP_WORD;
// 			new = ft_strjoin(new, token->str);
// 			del_token(head, &token);
// 		}
// 	}
// 	if (!token && word->q_state > 0)
// 		exit(printf("%s", QUOTE_ERROR));
// 	token->type = new_type;
// 	free(token->str);
// 	token->str = new;
// 	return (token);
// }

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
			// token->next->join = 1;
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
		else if (token->type > SPACE && token->next)
			token = try_join_token(head, token, word);
		else if (token)
			token = token->next;
		printf("REFINE TEST\n");
	}
	token_join_space(head, *head);
	printf("END OF REFINE\n");
}
