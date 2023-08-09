/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:12:45 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/08 22:23:16 by lsohler@stu      ###   ########.fr       */
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
