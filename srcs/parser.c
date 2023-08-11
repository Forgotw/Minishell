/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:40:28 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/11 21:31:31 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_token(t_token **token)
{
	t_token *tmp;

	tmp = *token;
	if (*token)
	{
		if ((*token)->prev)
			(*token)->prev->next = (*token)->next;
		if ((*token)->next)
			(*token)->next->prev = (*token)->prev;
		if (tmp)
		{
			if (tmp->str)
				free(tmp->str);
			free(tmp);
		}
	}
	*token = (*token)->next;
}

/* Si strjoin avec le next token est dans le dictionnaire join del token et next */
t_token	*try_join_token(t_token *token, t_word *word)
{
	char	*new;
	int		i;

	if (!token->next)
		return (token);
	i = 0;
	new = ft_strjoin(ft_strdup(token->str), token->next->str);
	printf("This is new now: %s\n", new);
	while (word->sep[i])
	{
		printf("test\n");
		if (!ft_strncmp(word->sep[i], new, ft_strlen(new)))
		{
			printf("test match found\n");
			del_token(&token);
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

/*
t_token	*expand_token(t_token *token, t_word *word)
{
	char	*new;


	new = NULL;
	del_token(&token);
	if (token)
	{
		if (token->type == DOL)
			token = do_double_dol(token);
		else if (token->type == Q_MARK)
			token = do_dol_q_mark(token);
		else if (token->type == WORD)
			token = do_expand_var(token);
		else if (token->type == O_BRACE)
			token = do_expand_var_brace(token);
		else
			exit (printf("%s %s\n", PARSE_ERROR, token->str));
	}
}*/

/* Del le token quote, tant que token != quote si il y'a des tokens les joins */
/* Tant que c'est un word je join new et str dans buff, free new , new devient buff */
t_token	*join_quoted_token(t_token *token, t_word *word)
{
	char	*new;

	new = NULL;
	word->q_state = token->type;
	del_token(&token);
	while (token && word->q_state > 0)
	{
		if (token->type == word->q_state)
			word->q_state = 0;
		else
		{
			//if (token->type == DOL && word->q_state == DQUOTE)
			//	token = expand_token(token, word);
			new = ft_strjoin(new, token->str);
			del_token(&token);
		}
	}
	if (!token && word->q_state > 0)
		exit(printf("%s", QUOTE_ERROR));
	token->type = WORD;
	token->str = new;
	if (token->next)
		token = token->next;
	return (token);
}

/* Join les words qui se suivent */
t_token	*join_word(t_token *token)
{
	char	*new;


	if (!token->next)
		return (token);
	while (token->next && token->type == WORD)
	{
		if (token->next->type == WORD)
		{
			new = ft_strjoin(new, token->next->str);
			del_token(&token);
		}
	}
}

/* Apres des quotes, join les words, si DQUOTE expand les var */
/* Expand les vars non quoted */
/* Supprime les tokens espaces */
/* Try join tokens par rapport au dictionnaire */
/* Checker la validité de la liste */
void	token_refiner(t_token *token, t_word *word)
{
	t_token *tmp;

	tmp = token;
	while (token)
	{
		if (token->type == QUOTE || token->type == DQUOTE)
			token = join_quoted_token(token, word);
		else if (token->type > SPACE)
			token = try_join_token(token, word);
		//else if (token->type == DOL)*/
		//else if (token->type == SPACE)
		//	del_token(&token);
		//else if (token->type != SPACE)
		else if (token)
			token = token->next;
	}
	/*token = tmp;
	while (token)
	{
		if (token->type == WORD)
			join_word(token);
		else if (token)
			token = token->next;
	}
	token = tmp;
*/
}
