/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:24:49 by lsohler           #+#    #+#             */
/*   Updated: 2022/11/22 17:43:23 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_add;
	void	*temp;

	if (!f || !lst || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		temp = f(lst->content);
		new_add = ft_lstnew(temp);
		if (!new_add)
		{
			del(temp);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, new_add);
		lst = lst->next;
	}
	return (new);
}
