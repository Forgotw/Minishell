/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:12:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/06 16:13:13 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

const char	*g_sep[] = {
	";", "|", "'", "\"", "{", "}", "(", ")", "<", ">",
	"*", "&", "$", "<<", ">>", "&&", "||", NULL
};

t_token	*new_token(char *str, t_word *word)
{
	t_token	*new;
	int		i;

	new = malloc(sizeof (t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	while (g_sep[i])
	{
		if (!ft_strncmp(g_sep[i], str, ft_strlen(g_sep[i])))
		{
			new->type = i;
			word->tok_size = ft_strlen(g_sep[i]);
			return (new);
		}
		i++;
	}
	i = 0;
	while (ft_strncmp(g_sep[i], str, ft_strlen(g_sep[i])))
	{
		i++;
	}
}

t_word	*word_init(void)
{
	t_word *word;

	word = malloc(sizeof (word));
	if (!word)
		return (NULL);
	word->d_q_state = 0;
	word->q_state = 0;
	word->tok_size = 0;
	word->w_size = 0;
}

t_token	*init_tokens(char *str)
{
	t_token	*token;
	t_word	*word;
	int		i;

	if (!str)
		return (NULL);
	word = word_init();
	i = 0;
	while (str[i])
	{
		token = new_token(&str[i], word)
	}
}
