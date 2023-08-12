/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:12:45 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/12 20:23:14 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tmp)
{
	// t_token *tmp;

	// tmp = tokens;
	if (!tmp)
		exit (printf("NO TOKENS\n"));
	while (tmp)
	{
		if (!tmp)
			printf("    TOKENS ERROR\n");
		printf("TOKEN ADRESS: %p\n", tmp);
		printf("Token_type: %i | Word: %p$\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
}

void	free_token(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens->next;
		if (tokens->str)
			free(tokens->str);
		free(tmp);
		tokens = tmp;
	}
}

int	main(int ac, char **av)
{
	t_token *tokens;

	if (ac != 2)
		//return (printf("argument error\n"));
		return (1);
	tokens = init_tokens(av[1]);
	printf("NEW       TOKEN      TYPE\n");
	print_tokens(tokens);
	free_token(tokens);
	free(tokens);
	//printf("NEW       TOKEN      TYPE\n");
	//while (tokens)
	//	del_token(&tokens);
}
