/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:49:49 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/26 14:56:35 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup(char **src)
{
	char	**array;

	if (!src)
		return (NULL);
	array = malloc(sizeof(ft_arrlen(src)) + 1);
	if (!array)
		return (NULL);
	while (array)
		*array++ = ft_strdup(*src++);
	*array++ = NULL;
	return (array);
}
