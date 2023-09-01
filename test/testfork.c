/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:36:11 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/30 11:36:32 by lsohler          ###   ########.fr       */
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
