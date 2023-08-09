/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:12:45 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/09 12:32:12 by lsohler          ###   ########.fr       */
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
	(void)ac;
	t_token *tokens;

	tokens = init_tokens(av[1]);
	print_tokens(tokens);
}
