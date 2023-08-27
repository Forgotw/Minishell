/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:49:49 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/27 12:45:57 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup(char **src)
{
	char	**array;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	array = malloc(sizeof(char *) * (ft_arrlen(src) + 1));
	if (!array)
		return (NULL);
	while (src[i])
	{
		array[i] = strdup(src[i]);
		i++;
	}
	array[i] = NULL;
	return (array);
}
