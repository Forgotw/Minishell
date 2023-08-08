/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:19:35 by lsohler           #+#    #+#             */
/*   Updated: 2022/10/26 16:50:54 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	a;
	int				i;

	str = (unsigned char *)s;
	a = (unsigned char)c;
	i = 0;
	while (i < (int)n)
	{
		if (str[i] == a)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
