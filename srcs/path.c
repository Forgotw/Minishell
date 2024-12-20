/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:32:57 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 20:31:02 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_array(t_shell *shell)
{
	char	**path_array;
	size_t	i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp((shell->env[i]), "PATH=", 5) == 0)
		{
			path_array = ft_split(shell->env[i], ':');
			return (path_array);
		}
		i++;
	}
	return (NULL);
}

int	cmd_file_error(char *cmd, int type)
{
	if (type == 0)
	{
		ft_putstr_fd("Minishell: ", STDERR);
		ft_putstr_fd(cmd, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
	}
	else
	{
		ft_putstr_fd("Minishell: ", STDERR);
		ft_putstr_fd(cmd, STDERR);
		ft_putendl_fd(": Command not found", STDERR);
	}
	return (127);
}

int	get_path(t_cmd *node, char **path_array)
{
	char		*tmp;
	struct stat	file_info;
	size_t		i;

	i = 0;
	while (path_array[i] != NULL)
	{
		tmp = ft_strjoin(path_array[i], "/");
		node->path = ft_strjoin(tmp, node->cmd);
		free(tmp);
		if (accces(node->cmd[0], F_OK) == 0
			&& stat(node->cmd[0], &file_info) == 0)
		{
			free_split(path_array);
			return (0);
		}
		free(node->path);
		i++;
	}
	free_split(path_array);
	return (cmd_file_error(node->cmd[0], 1));
}

int	check_relative_path(t_cmd *node)
{
	struct stat	file_info;

	if (accces(node->cmd[0], F_OK) == 0
		&& stat(node->cmd[0], &file_info) == 0)
	{
		node->path = node->cmd[0];
		return (0);
	}
	else
		return (cmd_file_error(node->cmd[0], 0));
}

int	check_absolute_path(t_cmd *node)
{
	char	**path_array;

	path_array = get_path_array(node->shell);
	if (path_array[0] == NULL)
		return (cmd_file_error(node->cmd[0], 0));
	else
		return (get_path(node, path_array));
}

int	get_path_type(char **cmd, t_cmd *node)
{
	if (cmd[1][0] == '/')
		return (check_relative_path(node));
	else
		return (check_absolute_path(node));
}