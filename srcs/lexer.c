/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:12:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/08 23:55:39 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*g_sep[] = {
	" ", ";", "|", "'", "\"", "{", "}", "(", ")", "<",
	">", "*", "&", "$", "?", "<<", ">>", "&&", "||", "$?", NULL
};

t_word	*word_init(void)
{
	t_word	*word;

	word = malloc(sizeof (word));
	if (!word)
		return (NULL);
	word->d_q_state = 0;
	word->q_state = 0;
	word->tok_size = 0;
	word->w_size = 0;
	
	return (word);
}

void	recognize_quoted(t_token *new, char *str, t_word *word)
{
	int	i;
	int	x;

	x =
	if (new->type == QUOTE)
		while (str[x])
}

void	recognize_word(t_token *new, char *str, t_word *word)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (new->type == QUOTE || new->type == DQUOTE)
		recognize_quoted(new, &str[1], word);
	else
	{
		while (ft_strncmp(g_sep[i], &str[x], ft_strlen(g_sep[i])) && str[x])
		{
			if (g_sep[i + 1] == NULL)
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
	while (g_sep[i])
	{
		if (!ft_strncmp(g_sep[i], str, ft_strlen(g_sep[i])))
		{
			new->type = i;
			if (new->type == QUOTE || new->type == DQUOTE)
				break;
			new->str = ft_strdup(g_sep[i]);
			word->tok_size = ft_strlen(g_sep[i]);
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
		i += word->tok_size;
		token = token->next;
	}
	return (token_start);
}
