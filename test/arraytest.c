/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraytest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:20:03 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/22 18:41:09 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>


size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

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

int	main(int ac, char **av)
{
	char	**cmd;
	int		i;

	i = 1;
	cmd = NULL;
	if (ac > 1)
	{
		while (i != ac)
		{
			cmd = ft_arraddline(cmd, av[i]);
			i++;
		}
		printf("This is the new array\n");
		i = 0;
		while (cmd[i])
		{
			printf("Str added: %s\n", cmd[i]);
			i++;
		}
		free_array(cmd);
	}
}