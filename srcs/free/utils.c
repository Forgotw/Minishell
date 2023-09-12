/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:24:05 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 20:39:50 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fdlist	*new_fd_node(int fd)
{
	t_fdlist	*new;

	new = malloc(sizeof(t_fdlist));
	new->fd = fd;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	fd_collector(t_fdlist **fdlist, int fd)
{
	t_address	*tmp;

	if (*fdlist == NULL)
		*fdlist = new_fd_node(fd);
	else
	{
		tmp = *fdlist;
		while (tmp->next)
		{
			
			tmp = tmp->next;
		}
		tmp->next = new_fd_node(fd);
	}
}

void	close_all_fd(t_fdlist *fdlsit)
{
	t_fdlist	*tmp;

	while (fdlist)
	{
		tmp = fdlist->next;
		close(fdlsit->fd)
		free(fdlsit);
		fdlsit = tmp;
	}
}
