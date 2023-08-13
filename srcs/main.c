/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:12:45 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/13 14:12:19 by lsohler          ###   ########.fr       */
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
		//printf("TOKEN ADRESS: %p\n", tmp);
		printf("Token_type: %i | Word: $%s$\n", tmp->type, tmp->str);
		printf("Str adress: %p\n", tmp->str);
		tmp = tmp->next;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->str)
			free(token->str);
		free(token);
		token = tmp;
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
	//free(tokens);
	//printf("NEW       TOKEN      TYPE\n");
	//while (tokens)
	//	del_token(&tokens);
}
