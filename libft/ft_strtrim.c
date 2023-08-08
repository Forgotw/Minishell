/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:44:20 by lsohler           #+#    #+#             */
/*   Updated: 2022/10/26 11:15:01 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int x)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = malloc(x * sizeof(char) + 1);
	if (!cpy)
		return (NULL);
	while (i < x)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	ft_tabpos1(char const *s1, char const *set)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (set[i] != '\0')
	{	
		if (s1[y] == set[i])
		{
			y++;
			i = 0;
		}
		if (s1[y] != set[i])
		{
			i++;
		}
	}
	return (y);
}

int	ft_tabpos2(char const *s1, char const *set)
{
	int	i;
	int	y;

	y = ft_strlen(s1) - 1;
	i = 0;
	while (set[i] != '\0')
	{
		if (s1[y] == set[i])
		{
			y--;
			i = 0;
		}
		if (s1[y] != set[i])
		{
			i++;
		}
	}
	return (y);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		x;
	int		y;
	char	*s2;

	x = ft_tabpos1(s1, set);
	y = ft_tabpos2(s1, set);
	if (y - x < 0)
		return (ft_strndup(s1, 0));
	s2 = ft_strndup(&s1[x], y - x + 1);
	return (s2);
}
