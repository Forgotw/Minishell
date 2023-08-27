/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:46:47 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/08/27 11:48:36 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>

int main(int ac, char **av, char **env)
{
	int	i = 0;
	(void)ac;
	(void)av;

	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}