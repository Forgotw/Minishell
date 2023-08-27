/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:38:01 by lsohler           #+#    #+#             */
/*   Updated: 2022/11/04 17:53:30 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char const *s, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			x++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (x);
}

char	*ft_worddup(char const *s, int len)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (s[i] != '\0' && i < len)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_splitword(char **array, char const *s, char c)
{
	int	i;
	int	x;
	int	a;

	i = 0;
	x = 0;
	a = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i + x] != '\0' && s[i + x] != c)
			x++;
		if (x > 0)
		{
			array[a++] = ft_worddup(&s[i], x);
			i = i + x;
			x = 0;
		}
	}
	array[a] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		x;
	char	**array;

	if (!s)
		return (NULL);
	x = ft_count(s, c);
	array = malloc(sizeof(char *) * (x + 1));
	if (!array)
		return (NULL);
	ft_splitword(array, s, c);
	return (array);
}
