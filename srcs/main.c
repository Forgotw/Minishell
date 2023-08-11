/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:12:45 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/11 19:03:59 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("Token_type: %i | Word: %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	t_token *tokens;

	if (ac != 2)
		return (printf("argument error\n"));
	tokens = init_tokens(av[1]);
	printf("NEW       TOKEN      TYPE\n");
	print_tokens(tokens);
	while (tokens)
		del_token(&tokens);
}
