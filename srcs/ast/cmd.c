/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:32:12 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/02 13:31:27 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_cmd_array(t_token **tok, char ***cmd_array_ptr, int *i_ptr)
{
	t_token	*token;
	int		i;
	char	**cmd_array;

	token = *tok;
	i = *i_ptr;
	cmd_array = *cmd_array_ptr;
	while (token->join && token->next)
	{
		if (!cmd_array[i])
			cmd_array = array_add_str(cmd_array, ft_strdup(token->str));
		else
			cmd_array[i] = ft_strjoin(cmd_array[i], ft_strdup(token->str));
		token = token->next;
		if (token->join == 0)
		{
			cmd_array[i] = ft_strjoin(cmd_array[i], ft_strdup(token->str));
			token = token->next;
			i++;
			break ;
		}	
	}
	*i_ptr = i;
	*tok = token;
	*cmd_array_ptr = cmd_array;
}

char	**create_cmd_array(t_token *token)
{
	char	**cmd_array;
	int		i;

	i = 0;
	cmd_array = NULL;
	while (token)
	{
		if (token->join && token->next)
			join_cmd_array(&token, &cmd_array, &i);
		if (token)
		{
			cmd_array = array_add_str(cmd_array, ft_strdup(token->str));
			token = token->next;
		}
		i++;
	}
	return (cmd_array);
}
