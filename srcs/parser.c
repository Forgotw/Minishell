/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:40:28 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/13 13:52:40 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Delete le token re-assigne les liaisons et free les malloc */
/* Si le token a remove est la head, on reassigne la head en consequence */
void	del_token(t_token **head, t_token **remove)
{
	t_token	*tmp;

	tmp = (*remove)->next;
	if (*remove)
	{
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

/* Si la combinaison du token et du next token est dans le dictionnaire */
/* On join les deux, on free et le token devient la combinaison */
t_token	*try_join_token(t_token **head, t_token *token, t_word *word)
{
	char	*new;
	int		i;

	if (!token->next)
		return (token);
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
t_token	*join_quoted_token(t_token **head, t_token *token, t_word *word)
{
	char	*new;

	new = NULL;
	word->q_state = token->type;
	del_token(head, &token);
	while (token && word->q_state > 0)
	{
		if (token->type == word->q_state)
			word->q_state = 0;
		else
		{
			//if (token->type == DOL && word->q_state == DQUOTE)
			//	token = expand_token(token, word);
			new = ft_strjoin(new, token->str);
			del_token(head, &token);
		}
	}
	if (!token && word->q_state > 0)
		exit(printf("%s", QUOTE_ERROR));
	token->type = WORD;
	// if (!new)
	// 	token->str = NULL;
	// else
	free(token->str);
	token->str = new;
	printf("New token type: %i str: %s\n", token->type, token->str);
	token = token->next;
	return (token);
}

/* Join les words qui se suivent */
t_token	*join_word(t_token **head, t_token *token)
{
	char	*new;


	if (!token->next)
		return (token);
	while (token->next && token->type == WORD)
	{
		if (token->next->type == WORD)
		{
			new = ft_strjoin(new, token->next->str);
			del_token(head, &token);
		}
	}
	return (token);
}

/* Apres des quotes, join les words, si DQUOTE expand les var */
/* Expand les vars non quoted */
/* Supprime les tokens espaces */
/* Try join tokens par rapport au dictionnaire */
/* Checker la validité de la liste */
void	token_refiner(t_token **head, t_word *word)
{
	t_token *token;

	token = *head;
	while (token && token->next != NULL)
	{
		if (token->type == QUOTE || token->type == DQUOTE)
			token = join_quoted_token(head, token, word);
		else if (token->type > SPACE && token->next)
			token = try_join_token(head, token, word);
		//else if (token->type == DOL)*/
		//else if (token->type == SPACE)
		//	del_token(&token);
		//else if (token->type != SPACE)
		else if (token)
			token = token->next;
		if (token)
		{
			printf("        WE did not LOST TOKEN !!!!!!\n");
			printf("        IN REFINER: TOKEN ADRESS: %p\n", token);
			printf("        IN REFINER: Token_type: %i | Word: %s$\n", token->type, token->str);
		}
	}
	//while (tokens)
	//{
	//	printf("   IN REFINER: Token_type: %p | Word: %p$\n", &tokens->type, tokens->str);
	//	tokens = tokens->next;
//	}
	//token = tmp;
	//print_tokens(tmp);
	//token = tmp;
	/*while (token)
	{
		if (token->type == WORD)
			join_word(token);
		else if (token)
			token = token->next;
	}
	token = tmp;
*/
}
