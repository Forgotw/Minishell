/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:12:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/24 14:36:27 by lsohler@stu      ###   ########.fr       */
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
	return (word);
}

void	recognize_word(t_token *new, char *arg, t_word *word)
{
	int	x;
	int	i;
	int	w_state;

	x = 0;
	i = 0;
	w_state = 0;
	while (ft_strncmp(word->sep[i], &arg[x],
			ft_strlen(word->sep[i])) && arg[x])
	{
		if (!ft_strncmp("*", &arg[x], 1))
			w_state = 1;
		if (word->sep[i + 1] == NULL)
		{
			x++;
			i = -1;
		}
		i++;
	}
	new->str = ft_strndup(arg, x);
	new->type = WORD;
	if (w_state)
		new->type = WILDCARD;
	word->tok_size = ft_strlen(new->str);
}

t_token	*new_token(char *arg, t_word *word)
{
	t_token	*new;
	int		i;

	new = malloc(sizeof (t_token) + 1);
	if (!new)
		return (NULL);
	new->type = -2;
	new->join = 0;
	new->str = NULL;
	new->next = NULL;
	new->prev = NULL;
	i = 0;
	while (word->sep[i])
	{
		if (!ft_strncmp(word->sep[i], arg, ft_strlen(word->sep[i])))
		{
			new->type = i;
			new->str = ft_strdup(word->sep[i]);
			word->tok_size = ft_strlen(word->sep[i]);
			return (new);
		}
		i++;
	}
	recognize_word(new, arg, word);
	return (new);
}

t_token	*init_tokens(char *arg)
{
	t_token	*token;
	t_token	*token_start;
	t_word	*word;
	int		i;

	word = word_init();
	i = 0;
	token = new_token(&arg[i], word);
	token_start = token;
	i += word->tok_size;
	while (arg[i])
	{
		token->next = new_token(&arg[i], word);
		token->next->prev = token;
		i += word->tok_size;
		token = token->next;
	}
	print_tokens(token_start);
	token_refiner(&token_start, word);
	free_array((char **)word->sep);
	free(word);
	return (token_start);
}
