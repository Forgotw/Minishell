/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:21:14 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/10 12:01:38 by lsohler          ###   ########.fr       */
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
		token->str = ft_itoa(ret_status);
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

t_token	*token_join_brace(t_token **head, t_token *token)
{
	char	*new;
	int		brace_state;

	new = NULL;
	brace_state = 1;
	del_token(head, &token);
	del_token(head, &token);
	while (token && brace_state)
	{
		if (token->type == C_BRACE)
			brace_state = 0;
		else
		{
			new = ft_strjoin(new, token->str);
			del_token(head, &token);
		}
	}
	if (!token && brace_state > 0)
		exit(printf("%s", BRACE_ERROR));
	token->type = EXP_WORD;
	free(token->str);
	token->str = new;
	return (token);
}

t_token	*token_dol_join(t_token **head, t_token *token)
{
	del_token(head, &token);
	token->type = EXP_WORD;
	return (token);
}

t_token	*token_dol_type(t_token **head, t_token *token)
{
	if (!token->next || token->next->type == SPACE)
		token->type = WORD;
	else if (token->next->type == Q_MARK || token->next->type == DOL
		|| token->next->type == WORD)
		token = token_dol_join(head, token);
	else if (token->next->type == O_BRACE)
		token = token_join_brace(head, token);
	token = token->next;
	return (token);
}