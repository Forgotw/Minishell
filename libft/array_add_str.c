/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_add_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:41:19 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/22 18:41:38 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**array_add_str(char **arr, char *line)
{
	char	**rtn;
	size_t	size;
	size_t	i;

	if (arr == NULL)
		size = 1;
	else
		size = ft_arrlen(arr) + 1;
	rtn = malloc(sizeof(char *) * (size + 1));
	if (rtn == NULL)
		return (NULL);
	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		rtn[i] = arr[i];
		i++;
	}
	rtn[i] = line;
	rtn[i + 1] = NULL;
	if (arr)
		free(arr);
	return (rtn);
}