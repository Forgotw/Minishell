/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:13:36 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 17:42:39 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_ret_status(int *status)
{
	if (WIFEXITED(*status))
		ret_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		ret_status = WTERMSIG(*status) + 128;
	else
		ret_status = *status;
}

void	boolean_link(t_cmd *node, int *status)
{
	/* si la commande renvoie 0:  OK */
	/* si la commande renvoie !0: KO */
	/* si link = AND et que OK, TRUE */
	/* else FALSE */
	/* si link = OR et que KO, TRUE  */
	/* else FALSE */
	(void)status;
	if (node->linktype == AND && !ret_status)
		node->shell->status = TRUE;
	else if (node->linktype == AND && ret_status)
		node->shell->status = FALSE;
	else if (node->linktype == OR && ret_status)
		node->shell->status = TRUE;
	else if (node->linktype == OR && !ret_status)
		node->shell->status = FALSE;
}

/*	if (node->shell->status == TRUE)
		execute_cmd(node, status);
	fprintf(stdout, "\033[35;1mstatus: %i\033[0m\n", *status);
	if (WIFEXITED(*status))
	{
		ret_status = WEXITSTATUS(*status);
		fprintf(stdout, "\033[35;1mWEXITSTATUS(status): %i\033[0m\n", ret_status);
	}
	fprintf(stdout, "\033[35;1mnode->shell->status: %i\033[0m\n", node->shell->status);
	if (node->linktype == AND)
	{
		fprintf(stdout, "\033[36;1mAND TYPE\033[0m\n");
		if ((WIFEXITED(*status) && WEXITSTATUS(*status)) || *status)
			node->shell->status = FALSE;
		else
			node->shell->status = TRUE;
	}
	else if (node->linktype == OR)
	{
		fprintf(stdout, "\033[36;1mOR TYPE\033[0m\n");
		if ((WIFEXITED(*status) && !WEXITSTATUS(*status)) || !*status)
			node->shell->status = FALSE;
		else
			node->shell->status = TRUE;
	}
	if (node->shell->status == 1)
		fprintf(stdout, "\033[32;1m TRUE \033[0m\n");
	if (node->shell->status == 0)
		fprintf(stdout, "\033[31;1m FALSE \033[0m\n");
	if (node->next)
		node = node->next;*/