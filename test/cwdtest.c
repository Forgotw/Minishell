/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwdtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:01:45 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 13:37:06 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

int	main(int ac, char **av)
{
	char	*buff;
	int		i;

	(void)ac;
	i = 1;
	buff = malloc(sizeof(char) * 1024);
	while (av[i])
	{
		printf("argument: %s\n", av[i]);
		if (getcwd(buff, 1024) != NULL)
			printf("%i Racine du système de fichiers : %s\n", i, buff);
		else
			printf("%i Erreur lors de l'obtention de la racine\n", i);
		if (chdir(av[i]) == 0)
		{
			printf("%i Répertoire changé avec succès.\n", i);
				if (getcwd(buff, 1024) != NULL)
				printf("%i Nouvelle Racine : %s\n", i, buff);
		}
		else
			printf("%i Erreur lors de l'obtention de la racine\n", i);
		i++;
	}
	return 0;
}
