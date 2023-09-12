/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:20:55 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 20:11:00 by lsohler          ###   ########.fr       */
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
		if (find[0] != '*'
			&& ft_strncmp(find_arr[i], tmp, ft_strlen(find_arr[i])))
			return (NULL);
		tmp = ft_strnstr(tmp, find_arr[i], ft_strlen((const char *)tmp));
		if (!tmp)
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
		perror("Error while getting current dir");
	wildc->dir = opendir(wildc->currentdir);
	if (!wildc->dir)
		perror("Error opening dir:");
	wildc->find_arr = ft_split(str, '*');
	wildc->find = ft_strdup(str);
	return (wildc);
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

t_token	*expand_wildcard(t_token **head, t_token *token)
{
	t_dtok		*toks;
	t_wildcard	*wc;

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
