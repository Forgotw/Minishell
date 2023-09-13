/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:24:05 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/13 15:47:18 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fdlist	*new_fd_node(int fd)
{
	t_fdlist	*new;

	new = malloc(sizeof(t_fdlist));
	new->fd = fd;
	new->next = NULL;
	return (new);
}

int	check_collector_fd(t_fdlist *list, int fd)
{
	while (list)
	{
		if (list->fd == fd)
			return (1);
		list = list->next;
	}
	return (0);
}

void	fd_collector(t_fdlist **fdlist, int fd)
{
	t_fdlist	*tmp;

	if (*fdlist == NULL)
		*fdlist = new_fd_node(fd);
	else
	{
		if (check_collector_fd(*fdlist, fd))
			return ;
		tmp = *fdlist;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_fd_node(fd);
	}
}

void	close_all_fd(t_fdlist *fdlist)
{
	t_fdlist	*tmp;

	while (fdlist)
	{
		tmp = fdlist->next;
		close(fdlist->fd);
		free(fdlist);
		fdlist = tmp;
	}
}
