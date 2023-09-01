/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:32:12 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/01 16:38:56 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_cmd_array(t_token *token)
{
	char	**cmd_array;
	int		i;

	i = 0;
	cmd_array = malloc(sizeof (char *) * 2);
	while (token)
	{
		while (token->join && token->next)
		{
			if (!cmd_array[i])
				cmd_array = array_add_str(cmd_array, ft_strdup(token->str));
			else
				cmd_array[i] = ft_strjoin(cmd_array[i], token->str);
			token = token->next;
			if (token->join == 0)
			{
				cmd_array[i] = ft_strjoin(cmd_array[i], token->str);
				token = token->next;
				i++;
				break ;
			}	
		}
		if (token)
			cmd_array = array_add_str(cmd_array, token->str);
		i++;
	}
	return (cmd_array);
}