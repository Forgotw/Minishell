/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:40:28 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/08 16:33:14 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_r_token(t_token **tokens)
{
	t_token	*r_token;

	if (!tokens)
		return (NULL);
	r_token = malloc(sizeof (t_token));
	
}

t_token	*refine_tokens(t_token *tokens)
{
	t_token	*r_tokens;

	r_tokens = new_r_token(&tokens);
}