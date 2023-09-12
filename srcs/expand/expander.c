/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:21:14 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 20:11:05 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* Chercher dans la str $, a str[i] == $ , tant que  alnum ou _ ii++*/
/* De str[i]  a str[ii] chercher la var */
/* new = join de (str[0] a str[i])+var puis new = join de new et str[ii]*/
t_token	*expand_return(t_token *token, t_shell *shell)
{
	(void)shell;
	if (!ft_strcmp(token->str, "?"))
	{
		free(token->str);
		token->str = ft_itoa(g_status);
	}
	else
	{
		free(token->str);
		token->str = ft_strdup("$PID$");
	}
	token = token->next;
	return (token);
}

t_token	*expand_var(t_token **head, t_token *token, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	if (!ft_strcmp(token->str, "?") || !ft_strcmp(token->str, "$"))
		return (expand_return(token, shell));
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], token->str, ft_strlen(token->str)))
		{
			len = ft_strlen(token->str);
			if (shell->env[i][len] && shell->env[i][len] == '=')
				len++;
			free(token->str);
			token->str = ft_strdup(&shell->env[i][len]);
			token = token->next;
			return (token);
		}
		i++;
	}
	del_token(head, &token);
	return (token);
}

t_token	*expand_token(t_token *token, t_shell *shell)
{
	t_token	*head;

	if (!token)
		return (NULL);
	head = token;
	while (token)
	{
		if (token->type == EXP_WORD)
			token = expand_var(&head, token, shell);
		else if (token->type == WILDCARD)
			token = expand_wildcard(&head, token);
		else
			token = token->next;
	}
	return (head);
}

void	insert_expand(t_token **head, t_token *token, t_dtok *toks)
{
	t_token		*tmp;

	tmp = token;
	toks->end->next = token->next;
	if (token->prev)
		token->prev->next = toks->start;
	if (token->next)
		token->next->prev = toks->end;
	token = toks->end;
	token->prev = tmp->prev;
	if (tmp == *head)
		*head = toks->start;
	free(tmp->str);
	free(tmp);
}
