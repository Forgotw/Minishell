/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:12:45 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 17:22:06 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tmp)
{
	// t_token *tmp;

	// tmp = tokens;
	if (!tmp)
		exit (printf("NO TOKENS\n"));
	while (tmp)
	{
		if (!tmp)
			printf("    TOKENS ERROR\n");
		//printf("TOKEN ADRESS: %p\n", tmp);
		printf("Token_type: %i | Word: $%s$\n", tmp->type, tmp->str);
		printf("token join: %i\n", tmp->join);
		//printf("Str adress: %p\n", tmp->str);
		tmp = tmp->next;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->str)
			free(token->str);
		free(token);
		token = tmp;
	}
}
/*
int	main(int ac, char **av, char **envp)
{
	int		ret;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->env = ft_arrdup(envp);
	ret = 0;
	if (ac < 2)
		return (printf("ARGUMENTS COUNT ERROR\n"));
	if (!ft_strcmp(av[1], "export"))
	{
		ret = export(&av[1], shell);
		print_export(shell->env);
		return (printf("RETURN VALUE OF EXPORT: %i\n", ret));
	}
	else if (!ft_strcmp(av[1], "unset"))
	{
		ret = unset(&av[1], shell);
		print_export(shell->env);
		return (printf("RETURN VALUE OF EXPORT: %i\n", ret));
	}
	return (0);
}*/

int	main(int ac, char **av, char **envp)
{
	t_token *tokens;
	t_cmd	*ast;

	(void)envp;
	if (ac != 2)
		//return (printf("argument error\n"));
		return (1);
	ret_status = 0;
	tokens = init_tokens(av[1]);
	printf("NEW       TOKEN      TYPE\n");
	print_tokens(tokens);
	syntax_checker(tokens);
	ast = create_ast(tokens);
	printf("AST DONE %p!\n", ast);
	executor_print(ast);
	free_token(tokens);
	ast_free(ast);
}
/*
char	*find_file(char *file, char *find, char **find_arr)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = file;
	while (find_arr[i])
	{
		tmp = strstr(tmp, find_arr[i]);
		if (!tmp)
			return (NULL);
		if (find[0] != '*' && strncmp(find_arr[i], tmp, strlen(find_arr[i])))
			return (NULL);
		tmp += strlen(find_arr[i]);
		i++;
	}
	if ((find[strlen(find) - 1]) != '*'
		&& strncmp(find_arr[i - 1],
			&file[strlen(file) - strlen(find_arr[i - 1])],
			strlen(find_arr[i - 1])))
		return (NULL);
	return (strdup(file));
}

int	main(int ac, char **av)
{
	char	*ret;
	char	**find_arr;
	char	currentdir[1024];
	DIR		*dir;
	struct dirent *entry;
	
	(void)ac;
	find_arr = ft_split(av[1], '*');
	printf("AV1: %s, AV2: %s\n", av[1], av[2]);
	ret = find_file(av[2], av[1], find_arr);
	printf("we found: %s\n", ret);
	free(find_arr);
	if (getcwd(currentdir, sizeof(currentdir)) != NULL)
		printf("Répertoire courant : %s\n", currentdir);
	chdir("/Users/lsohler/MiniShell/test");
	if (getcwd(currentdir, sizeof(currentdir)) != NULL)
		printf("Répertoire courant : %s\n", currentdir);
	dir = opendir(currentdir);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{ 
			printf("%s\n", entry->d_name);
		}
	}
	closedir(dir);
	return (0);
}*/
