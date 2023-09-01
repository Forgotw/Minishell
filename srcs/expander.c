/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:21:14 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/01 15:26:57 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* Chercher dans la str $, a str[i] == $ , tant que  alnum ou _ ii++*/
/* De str[i]  a str[ii] chercher la var */
/* new = join de (str[0] a str[i])+var puis new = join de new et str[ii]*/
t_token	*expand_return(t_token *token, t_shell *shell)
{
	if (!ft_strcmp(token->str, "$?"))
	{
		free(token->str);
		token->str = ft_itoa(shell->status);
	}
	token->type = WORD;
	return (token);
}

t_token	*expand_var(t_token *token, t_shell *shell)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strcmp(shell->env[i], &token->str[1]))
		{
			free(token->str);
			while (shell->env[i][y] || shell->env[i][y] != '=')
				y++;
			token->str = ft_strdup(&shell->env[i][y]);
			return (token);
		}
		i++;
	}
	free(token->str);
	token->str = malloc(sizeof(char));
	token->str[0] = '\0';
	return (token);
}

/*
t_token	*expand_braced_word(t_token **head, t_token *token)
{
	char	*new;
	int		brace_state;

	new = NULL;
	brace_state = 1;
	del_token(head, &token);
	while (token && brace_state)
	{
		if (token->type == C_BRACE)
			brace_state = 0;
		else if (token->type != WORD)
			exit(printf("%s\n", BAD_SUB));
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

t_token	*expand_word(t_token **head, t_token *token)
{
	char	*new;

	del_token(head, &token);
	if (token->type == O_BRACE)
		token = expand_braced_word(head, token);
	new = ft_strjoin(token->str, "<TO BE EXPANDED>");
	token->str = new;
	token->type = WORD;
	return (token);
}

t_token	*expand_var(t_token **head, t_token *token)
{
	if (!token)
		return (NULL);
	if (!token->next)
		token->type = WORD;
	else
	{
		if (token->type == DOL_Q_MARK)
			token = expand_dol_q_mark(token);
		else if (token->type == DOL_DOL)
			token = expand_dol_dol(token);
		else if (token->type == DOL && token->next)
		{
			if (token->next->type == WORD || token->next->type == O_BRACE)
				token = expand_word(head, token);
			else
				token->type = WORD;
		}
	}
	return (token);
}
*/
// char	**create_cmd_array(t_token *token)
// {
// 	char	**cmd_array;
// 	int		i;

// 	i = 0;
// 	cmd_array = malloc(sizeof (char *) + 1);
// 	while (token)
// 	{
// 		while (token->join && token->next)
// 		{
// 			if (!cmd_array[i])
// 				cmd_array = ft_strdup(token->str);
// 			else
// 				cmd_array[i] = ft_strjoin(cmd_array[i], token->str);
// 			token = token->next;
// 		}
// 	}
// }

t_token	*expand_token(t_token *token, t_shell *shell)
{
	t_token	*head;

	if (!token)
		return (NULL);
	head = token;
	while (token)
	{
		if (token->type == EXP_WORD)
			token = expand_var(token, shell);
		else if (token->type == WILDCARD)
			token = expand_wildcard(&head, token);
		else if (!ft_strcmp(token->str, "$?") || !ft_strcmp(token->str, "$$"))
			token = expand_return(token, shell);
		token = token->next;
	}
	return (token);
}

t_token	*token_join_brace(t_token **head, t_token *token)
{
	char	*new;
	int		brace_state;

	new = NULL;
	brace_state = 1;
	printf("test\n");
	del_token(head, &token);
	printf("test1\n");
	del_token(head, &token);
	printf("test2\n");
	while (token && brace_state)
	{printf("test while\n");
		if (token->type == C_BRACE)
			brace_state = 0;
		else
		{
			new = ft_strjoin(new, token->str);
			del_token(head, &token);
		}
	}
	printf("test after while\n");
	if (!token && brace_state > 0)
		exit(printf("%s", BRACE_ERROR));
	printf("test3\n");
	token->type = EXP_WORD;
	printf("test4\n");
	free(token->str);
	printf("test5\n");
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

/*

t_token	*expand_var(t_token **head, t_token *token)
{
	if (!token->next)
		token->type = WORD;
	else
	{
		if (token->type == DOL_Q_MARK)
			token = expand_dol_q_mark(token);
		else if (token->type == DOL_DOL)
			token = expand_dol_dol(token);
		else if (token->type == DOL && token->next)
		{
			if (token->next == WORD || token->next == O_BRACE)
				token = expand_word(head, token);
			else
				token->type == WORD;
		}
	}
	return (token);
}*/