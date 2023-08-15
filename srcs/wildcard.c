/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:20:55 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/15 22:17:16 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_file(char *file, char *find, char **find_arr)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = file;
	while (find_arr[i])
	{
		tmp = strstr(tmp, find_arr[i]);
		if (!tmp)
			return (NULL);
		if (find[0] != '*' && strncmp(find_arr[i], tmp, strlen(find_arr[i])))
			return (NULL);
		tmp += strlen(find_arr[i]);
		i++;
	}
	if ((find[strlen(find) - 1]) != '*'
		&& strncmp(find_arr[i - 1],
			&file[strlen(file) - strlen(find_arr[i - 1])],
			strlen(find_arr[i - 1])))
		return (NULL);
	return (strdup(file));
}

t_wildcard	*init_wildcard(char *str)
{
	t_wildcard	*wildc;

	if (getcwd(wildc->currentdir, sizeof(wildc->currentdir)) == NULL)
		printf("Error while getting current dir\n");
	wildc->dir = opendir(wildc->currentdir);
	if (!wildc->dir)
		printf("Error opening dir %s\n", wildc->currentdir);
	wildc->find_arr = ft_split(str, "*");
	wildc->find = str;
}

t_token	*new_word(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->type = WORD;
	new->str = NULL;
	new->prev = token;

}

t_token	*search_file(t_token *token, t_wildcard wc)
{
	char	*buff;
	t_token	*tmp;

	tmp = token;
	buff = NULL;
	if (token->str)
		free(token->str);
	token->str = NULL;
	while (wc->entry = readdir(wc->dir) != NULL)
	{
		if (wc->entry->d_type == DT_REG)
		{
			buff = find_file(wc->entry->d_name, wc->find, wc->find_arr);
			if (buff)
			{
				token->str = buff;
					if (token != tmp)
						token->next = new_word(token);
				token = token->next;
			}
		}
	}/* finir cette fonction, gerer token = token->next ou new ou pas*/
	return (token);
}

t_token *expand_wildcard(t_token **head, t_token *token)
{
	t_token		*tmp;
	t_wildcard	*wc;

	tmp = token->next;
	wc = init_wildcard(token->str);
	token = search_file(token, wc);
	if (token->str == NULL)
}

int	main(int ac, char **av)
{
	char	*ret;
	char	**find_arr;
	char	currentdir[1024];
	DIR		*dir;
	struct dirent *entry;
	
	(void)ac;
	find_arr = ft_split(av[1], '*');
	printf("AV1: %s, AV2: %s\n", av[1], av[2]);
	ret = find_file(av[2], av[1], find_arr);
	printf("we found: %s\n", ret);
	free(find_arr);
	if (getcwd(currentdir, sizeof(currentdir)) != NULL)
		printf("Répertoire courant : %s\n", currentdir);
	chdir("/Users/lsohler/MiniShell/test");
	if (getcwd(currentdir, sizeof(currentdir)) != NULL)
		printf("Répertoire courant : %s\n", currentdir);
	dir = opendir(currentdir);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{ 
			printf("%s\n", entry->d_name);
		}
	}
	closedir(dir);
	return (0);
}

/*
bo * our * 42Lau * ne
bonjoooooooo our 42Lau san ne
salutbonjour42Lausanne

bo nj our salut 42Lau san ne

tant que find
	si find == *
		find++;

	tant que file == find
		find++ et file++;
si les deux arrive a la fin ok 

split find *,
tant que find_arr
	tmp = strstr(file,find_arr)
	si find[0] != * et que strncmp(find_arr,tmp, len(find_arr)) != 0
		return (NULL)
	find_arr++;
si find[len(find - 1)] != * && strncmp(find_arr, tmp, len(tmp)) != 0
	return (NULL)
si tmp != NULL
	return (strdup(file));
*/