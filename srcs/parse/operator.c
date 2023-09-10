/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:03:40 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/01 15:06:00 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_sep_a(const char **sep)
{
	*sep++ = ft_strdup(" ");
	*sep++ = ft_strdup("|");
	*sep++ = ft_strdup("'");
	*sep++ = ft_strdup("\"");
	*sep++ = ft_strdup("{");
	*sep++ = ft_strdup("}");
	*sep++ = ft_strdup("(");
	*sep++ = ft_strdup(")");
	*sep++ = ft_strdup("<");
	*sep++ = ft_strdup(">");
	*sep++ = ft_strdup("&");
	*sep++ = ft_strdup("?");
	*sep++ = ft_strdup("$");
	*sep++ = ft_strdup("$?");
	*sep++ = ft_strdup("$$");
	*sep++ = ft_strdup("<<");
	*sep++ = ft_strdup(">>");
	*sep++ = ft_strdup("&&");
	*sep++ = ft_strdup("||");
	*sep++ = NULL;
}

const char	**init_sep(void)
{
	const char	**sep;

	sep = malloc(sizeof(char *) * 30);
	init_sep_a(sep);
	return (sep);
}
