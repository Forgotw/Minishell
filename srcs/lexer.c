/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:12:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/09 14:44:03 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*word_init(void)
{
	t_word	*word;

	word = malloc(sizeof (t_word));
	if (!word)
		return (NULL);
	word->d_q_state = 0;
	word->q_state = 0;
	word->tok_size = 0;
	word->sep = init_sep();
	int	i = 0;
	while (word->sep[i])
	{
		printf("sep: 0%s0\n", word->sep[i]);
		i++;
	}
	printf("finish printing sep\n");
	return (word);
}

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
			new->str = ft_strdup(word->sep[i]);
			word->tok_size = ft_strlen(word->sep[i]);
			return (new);
		}
		i++;
	}
	recognize_word(new, str, word);
	return (new);
}

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
	return (token_start);
}
