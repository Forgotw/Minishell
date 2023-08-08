/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:12:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/08 16:18:47 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

const char	*g_sep[] = {
	" ", ";", "|", "'", "\"", "{", "}", "(", ")", "<",
	">", "*", "&", "$", NULL
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

void	recognize_word(t_token *new, char *str, t_word *word)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	//printf("Word found at: 0%s0\n", str);
	while (ft_strncmp(g_sep[i], &str[x], ft_strlen(g_sep[i])) && str[x])
	{
		//printf("parcour g_sep: %s avec la lettre: 0%c0 len: %zu\n", g_sep[i], str[x], ft_strlen(g_sep[i]));
		if (g_sep[i + 1] == NULL)
		{
			//printf("fini de parcourir g_sep\n");
			x++;
			i = -1;
		}
		i++;
	}
	//printf("nombre de lettre dans le word: %x\n", x);
	new->str = ft_strndup(str, x);
	//printf("the strdup is: %s\n", new->str);
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
	new->next = NULL;
	new->prev = NULL;
	i = 0;
	while (g_sep[i])
	{
		if (!ft_strncmp(g_sep[i], str, ft_strlen(g_sep[i])))
		{
			//printf("lexical found\n");
			new->type = i;
			word->tok_size = ft_strlen(g_sep[i]);
			return (new);
		}
		i++;
	}
	//printf("found a word\n");
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
	//printf("toksize= %i\n", word->tok_size);
	while (str[i])
	{
		//printf("               i am here in the string 0%s0\n", &str[i]);
		token->next = new_token(&str[i], word);
		i += word->tok_size;
		//printf("toksize= %i\n", word->tok_size);
		token = token->next;
	}
	return (token_start);
}
