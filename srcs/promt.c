/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:14:47 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/26 15:28:28 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	promt(void)
{
	char	*input = NULL;
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
			exit (1);
		add_history(input);
		if (!ft_strncmp(input, "exit", 4))
			exit (0);
	}
}