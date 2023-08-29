/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:46:47 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/08/27 16:55:31 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>

int	ft_isdigit(int C)
{
	if (C >= '0' & C <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int C)
{
	if (C >= '0' && C <= '9')
		return (1);
	else if (C >= 'A' && C <= 'Z')
		return (1);
	else if (C >= 'a' && C <= 'z')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || (s1 == NULL && s2 == NULL))
		return (0);
	if (s1 == NULL)
		return (-1);
	if (s2 == NULL)
		return (1);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

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
		array[i] = ft_strdup(src[i]);
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
			if (ft_strcmp(array[i], array[i + 1]) > 0)
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

int	check_var_identifier(char *str)
{
	int	i;

	i = 1;
	printf("check var identifier\n");
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
void	print_array(char **array);

void	add_or_replace_var(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	printf("add or replace var\n");
	while (str[len] && str[len + 1] != '=')
		len++;
	printf("after len to =\n");
	while (env[i])
	{
	printf("Searching: %s IN: %s\n", str, env[i]);
		if (!ft_strncmp(str, env[i], len))
		{
			printf("before free test\n");
			free(env[i]);
			printf("before dup test\n");
			env[i] = ft_strdup(str);
			printf("after dup test\n");
			return ;
		}
		i++;
	}
	printf("before add to env\n");
	*env = *array_add_str(env, ft_strdup(str));
	printf("after add to env\n");
}

int	export_vars(char **cmd, char **env)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	printf("test1\n");
	while (cmd[i])
	{
		printf("this is the command: %s\n", cmd[i]);
		if (!cmd[i] || check_var_identifier(cmd[i]))
		{
			printf("%s %s `%s' %s\n", "Minishell:", "export:",
				cmd[i], ": not a valid identifier\n");
			ret = 1;
		}
		add_or_replace_var(cmd[i], env);
		printf("after add or replace\n");
		i++;
		printf("this is the end of while\n");
	}
	printf("return from export var\n");
	return (ret);
}

int	print_env(char **env)
{
	int		i;
	char	**sorted;

	i = 0;
	if (!env)
		return (1);
	sorted = ft_arrdup(env);
	ft_arrsort(sorted);
	while (sorted[i])
	{
		printf("declare -x ");
		printf("%s\n", sorted[i]);
		i++;
	}
	//free_array(sorted);
	return (0);
}

int	export(char **cmd, char **env)
{
	if (!cmd)
		return (-1);
	else if (!cmd[1])
		return (print_env(env));
	else
		return (export_vars(&cmd[1], env));
	return (0);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		printf("--- No array---\n");
	else
	{
		//printf("Array: ");
		while (array[i])
		{
			printf("%s\n", array[i]);
			i++;
		}
		printf("\n END OF ARRAY \n");
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	print_array(env);
	return (0);
}
