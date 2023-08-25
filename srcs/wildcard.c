/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:20:55 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/24 14:37:43 by lsohler@stu      ###   ########.fr       */
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
		tmp = ft_strnstr(tmp, find_arr[i], ft_strlen((const char *)tmp));
		if (!tmp)
			return (NULL);
		if (find[0] != '*' && ft_strncmp(find_arr[i], tmp, ft_strlen(find_arr[i])))
			return (NULL);
		tmp += ft_strlen(find_arr[i]);
		i++;
	}
	if ((find[ft_strlen(find) - 1]) != '*'
		&& ft_strncmp(find_arr[i - 1],
			&file[ft_strlen(file) - ft_strlen(find_arr[i - 1])],
			ft_strlen(find_arr[i - 1])))
		return (NULL);
	return (ft_strdup(file));
}

t_wildcard	*init_wildcard(char *str)
{
	t_wildcard	*wildc;

	wildc = malloc(sizeof(t_wildcard));
	wildc->buff = NULL;
	if (getcwd(wildc->currentdir, sizeof(wildc->currentdir)) == NULL)
		printf("Error while getting current dir\n");
	wildc->dir = opendir(wildc->currentdir);
	if (!wildc->dir)
		printf("Error opening dir %s\n", wildc->currentdir);
	wildc->find_arr = ft_split(str, '*');
	wildc->find = ft_strdup(str);
	return (wildc);
}

t_token	*new_word(t_token *token, char *buff)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->type = WORD;
	new->join = 0;
	new->str = strdup(buff);
	if (buff)
		free(buff);
	new->prev = token;
	new->next = NULL;
	return (new);
}

void	search_dir(t_wildcard *wc, t_dtok *toks,
	t_token *token, t_token **tmp)
{
	while (wc->entry != NULL)
	{
		if (wc->entry->d_type == DT_REG || wc->entry->d_type == DT_DIR)
		{
			wc->buff = find_file(wc->entry->d_name, wc->find, wc->find_arr);
			if (wc->buff && wc->buff[0] != '.')
			{
				if (!toks->start)
				{
					toks->start = new_word(token->prev, wc->buff);
					*tmp = toks->start;
				}
				else
				{
					toks->start->next = new_word(token, wc->buff);
					toks->start = toks->start->next;
				}
			}
		}
		wc->entry = readdir(wc->dir);
	}
}

/* On rajoute a la suite du token wildcard des tokens: */
/*    word avec buff si on trouve un fichier */
/* on retourne le token du dernier fichier trouvé */
t_dtok	*search_file(t_token *token, t_wildcard *wc)
{
	t_dtok	*toks;
	t_token	*tmp;

	toks = malloc(sizeof(t_dtok));
	toks->start = NULL;
	toks->end = NULL;
	tmp = NULL;
	token->type = WILDCARD;
	wc->entry = readdir(wc->dir);
	search_dir(wc, toks, token, &tmp);
	closedir(wc->dir);
	toks->end = toks->start;
	toks->start = tmp;
	return (toks);
}

void	insert_expand(t_token **head, t_token *token, t_dtok *toks)
{
	t_token		*tmp;

	tmp = token;
	toks->end->next = token->next;
	if (token->prev)
		token->prev->next = toks->start;
	if (token->next)
		token->next->prev = toks->end;
	token = toks->end;
	token->prev = tmp->prev;
	if (tmp == *head)
		*head = toks->start;
	free(tmp->str);
	free(tmp);
}

t_token	*expand_wildcard(t_token **head, t_token *token)
{
	t_dtok		*toks;
	t_wildcard	*wc;
	//t_token		*tmp;

	//tmp = token;
	wc = init_wildcard(token->str);
	toks = search_file(token, wc);
	if (toks->start)
		insert_expand(head, token, toks);
	token = token->next;
	free(toks);
	if (wc->find_arr)
		free_array(wc->find_arr);
	free(wc->find);
	free(wc);
	return (token);
}

/*
	(void)head;
	tmp = token;
	wc = init_wildcard(tmp->str);
	toks = search_file(tmp, wc);
	printf("    EXP      where am i start: str:%s type:%i\n", toks->start->str, toks->start->type);
	printf("    EXP      where am i end: str:%s type:%i\n", toks->end->str, toks->end->type);
	printf("    EXP      where am i end next add: %p\n", toks->end->next);
	// printf("where am i token: str:%s type:%i\n", token->str, token->type);
	// printf("where am i tmp prev: str:%s type:%i\n", tmp->prev->str, tmp->prev->type);
	// printf("what is tmp: str:%s type:%i\n", tmp->str, tmp->type);
	// printf("\n\nAddress 1: %p\nAddres 2: %p\n\n\n", tmp, token);
	//printf("what is tmp->prev: str:%s type:%i\n", tmp->prev->str, tmp->prev->type);
	if (toks->start != toks->end)
	{
		
	}
	// printf("where am i token: str:%s type:%i\n", token->str, token->type);
	// printf("where am i next adress: %p\n", token);
	if (wc->find)
		free(wc->find);
	if (wc->find_arr)
		free_array(wc->find_arr);
	free(wc);
	//printf("where am i token: str:%s type:%i\n", token->str, token->type);
	//printf("where am i token   2: str:%s type:%i\n", token->str, token->type);
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
}*/

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