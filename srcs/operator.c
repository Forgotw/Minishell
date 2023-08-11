/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:03:40 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/11 18:39:42 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int			i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
	{
		free(array);
	}
}

void	init_sep_a(const char **sep)
{
	*sep++ = ft_strdup(" ");
	*sep++ = ft_strdup(";");
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
	*sep++ = ft_strdup("$");
	*sep++ = ft_strdup("?");
	*sep++ = ft_strdup("<<");
	*sep++ = ft_strdup(">>");
	*sep++ = ft_strdup("&&");
	*sep++ = ft_strdup("||");
	*sep++ = ft_strdup("$?");
}

const char	**init_sep(void)
{
	const char	**sep;

	sep = malloc(sizeof(const char *) * 30);
	init_sep_a(sep);
	//init_sep_b(sep);
	return (sep);
}

/*void	init_sep_a(const char ***tmp)
{
	const char **sep;

	sep = *tmp;
	*sep++ = ft_strdup(" ");
	*sep++ = ft_strdup(";");
	*sep++ = ft_strdup("|");
	*sep++ = ft_strdup("'");
	*sep++ = ft_strdup("\"");
	*sep++ = ft_strdup("{");
	*sep++ = ft_strdup("}");
	*sep++ = ft_strdup("(");
	*sep++ = ft_strdup(")");
	*sep++ = ft_strdup("<");
	*sep++ = ft_strdup(">");
	*sep++ = ft_strdup("*");
	*sep++ = ft_strdup("&");
	*sep++ = ft_strdup("$");
	*sep++ = ft_strdup("?");
	*sep++ = ft_strdup("<<");
	*sep++ = ft_strdup(">>");
	*sep++ = ft_strdup("&&");
	*sep++ = ft_strdup("||");
	*sep++ = ft_strdup("$?");
}

void	init_sep_b(const char ***tmp)
{
	const char **sep;

	sep = *tmp;
	*sep++ = ft_strdup("<&");
	*sep++ = ft_strdup(">&");
	*sep++ = ft_strdup("<<&");
	*sep++ = ft_strdup(">>&");
	*sep++ = ft_strdup("~");
	*sep++ = ft_strdup("$$");
	*sep++ = NULL;
}*/

/*void	init_sep_a(const char **sep)
{
	sep[0] = ft_strdup(" ");
	sep[1] = ft_strdup(";");
	sep[2] = ft_strdup("|");
	sep[3] = ft_strdup("'");
	sep[4] = ft_strdup("\"");
	sep[5] = ft_strdup("{");
	sep[6] = ft_strdup("}");
	sep[7] = ft_strdup("(");
	sep[8] = ft_strdup(")");
	sep[9] = ft_strdup("<");
	sep[10] = ft_strdup(">");
	sep[11] = ft_strdup("*");
	sep[12] = ft_strdup("&");
	sep[13] = ft_strdup("$");
	sep[14] = ft_strdup("?");
	sep[15] = ft_strdup("<<");
	sep[16] = ft_strdup(">>");
	sep[17] = ft_strdup("&&");
	sep[18] = ft_strdup("||");
	sep[19] = ft_strdup("$?");
}

void	init_sep_b(const char **sep)
{
	sep[20] = ft_strdup("<&");
	sep[21] = ft_strdup(">&");
	sep[22] = ft_strdup("<<&");
	sep[23] = ft_strdup(">>&");
	sep[24] = ft_strdup("~");
	sep[25] = ft_strdup("$$");
	sep[26] = NULL;
}
*/