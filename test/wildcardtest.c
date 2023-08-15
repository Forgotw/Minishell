/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcardtest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:33:16 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/15 17:38:25 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_file(char *file, char *find)
{
	char	*tmp;
	char	**find_arr;
	int		i;

	i = 0;
	find_arr = ft_split(find, '*');
	while (find_arr[i])
	{
		tmp = strstr(file, find_arr[i]);
		if (!tmp)
			return (NULL);
		if (find[0] != '*' && strncmp(find_arr[i], tmp, strlen(find_arr[i])))
			return (NULL);
		i++;
	}
	if ((find[strlen(find) - 1]) && strncmp(find_arr[i - 1], tmp, strlen(tmp)))
		return (NULL);
	return (strdup(tmp));
}

int	main(int ac, char **av)
{
	char	*ret;

	if (ac != 2)
		return -1;
	ret = find_file(av[1], av[2]);
	printf("%s\n", ret);
	return 0;
}