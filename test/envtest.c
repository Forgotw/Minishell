/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:46:47 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/08/27 12:44:59 by lsohler          ###   ########.fr       */
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

void	ft_arrsort(char **array)
{
	int		len;
	int		i;
	int		swapped;
	char	*tmp;

	i = 0;
	swapped = 1;
	len = ft_arrlen(array);
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < len - 1)
		{
			if (strcmp(array[i], array[i + 1]) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

int main(int ac, char **av, char **env)
{
	int	i = 0;
	(void)ac;
	(void)av;
	char **array;
	
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	i = 0;
	printf("\nNOW DUPING ARRAY\n");
	array = ft_arrdup(env);
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	i = 0;
	printf("\n\nNOW SORTING ARRAY\n\n");
	ft_arrsort(array);
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}
