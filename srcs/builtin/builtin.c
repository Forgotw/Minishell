/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:48:11 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/26 16:08:45 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtin_dic(const char **dict)
{
	*dict++ = ft_strdup("cd");
	*dict++ = ft_strdup("echo");
	*dict++ = ft_strdup("env");
	*dict++ = ft_strdup("exit");
	*dict++ = ft_strdup("export");
	*dict++ = ft_strdup("pwd");
	*dict++ = ft_strdup("unset");
	*dict++ = NULL;
}

const char	**builtin_dic()
{
	const char	**dict;

	dict = malloc (sizeof(char *) * 8);
	init_builtin_dic(dict);
	return (dict);
}
