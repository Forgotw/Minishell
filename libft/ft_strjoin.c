/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:32:13 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/08 21:23:09 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, ft_strlen(s1) + 1);
	ft_strlcat(s3, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (s3);
}
