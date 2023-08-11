/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:00:50 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/11 18:52:09 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*word_init(void)
{
	t_word	*word;

	word = malloc(sizeof (t_word));
	if (!word)
		return (NULL);
	word->q_state = 0;
	word->tok_size = 0;
	word->sep = init_sep();
	int	i = 0;
	return (word);
}

/* Alloue dans le tokens une str j'usqu'a trouver un operateur */
void	recognize_word(t_token *new, char *str, t_word *word)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (ft_strncmp(word->sep[i], &str[x],
			ft_strlen(word->sep[i])) && str[x])
	{
		if (word->sep[i + 1] == NULL)
		{
			x++;
			i = -1;
		}
		i++;
	}
	new->str = ft_strndup(str, x);
	new->type = WORD;
	word->tok_size = ft_strlen(new->str);
}

/* Checker dans la string les VAR les expand puis alloue a new->str le word avec les vars expanded */
void	expand_word(t_token *new, char *str, t_word *word)
{

}

/* Reconnais les quotes et copie la string j'usqu'a une dquote ou quote ou fin de str */
/* Si rencontre un $ appel expand word avec la str de new->str */
/* Si fin de str A FAIRE*/
void	recognize_quoted_word(t_token *new, char *str, t_word *word)
{
	int		i;

	word->q_state = 1;
	while (str[i])
	{
		if (new->type == QUOTE && !ft_strcmp(str[i], word->sep[QUOTE]))
			word->q_state = 0;
		else if (new->type == DQUOTE && !ft_strcmp(str[i], word->sep[DQUOTE]))
		{
			word->q_state = 0;
			if (!ft_strcmp(str[i], word->sep[DOL]))
				new->type = DOL;
		}
		i++;
	}
	new->str = ft_strndup(str, i);
	if (new->type = DOL)
		expand_word(new, new->str, word);
	new->type = WORD;
}


t_token	*new_token(char *str, t_word *word)
{
	t_token	*new;
	int		i;

	new = malloc(sizeof (t_token));
	if (!new)
		return (NULL);
	new->type = -2;
	new->next = NULL;
	new->prev = NULL;
	i = 0;
	while (word->sep[i])
	{
		if (!ft_strncmp(word->sep[i], str, ft_strlen(word->sep[i])))
		{
			new->type = i;
			if (new->type == QUOTE || new->type == DQUOTE)
				recognize_quoted_word(new, str, word);
			else if (new->type == DOL)
			{
				expand_word(new, str, word);
				new->type = WORD;
			}
			else
				get_token(new, str, word);
			return (new);
		}
		i++;
	}
	recognize_word(new, str, word);
	return (new);
}

/*Initialise la liste de tokens et renvoie un ptr sur le premier de la liste */
t_token	*init_tokens(char *str)
{
	t_token	*token;
	t_token	*token_start;
	t_word	*word;
	int		i;

	if (!str)
		return (NULL);
	word = word_init();
	i = 0;
	token = new_token(&str[i], word);
	token_start = token;
	i += word->tok_size;
	while (str[i])
	{
		token->next = new_token(&str[i], word);
		token->next->prev = token;
		i += word->tok_size;
		token = token->next;
	}
	token_refiner(&token_start, word);
	return (token_start);
}