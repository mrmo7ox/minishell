/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:44:05 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/04 14:51:38 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// bool	create_file(char *path)
// {
// }

bool	exec_redirec(t_tk *token, t_gc **garbage)
{
	t_redic	*curr;
	char	**parts;

	(void)garbage;
	(void)parts;
	curr = token->redics;
	printf("======[TEST]======\n");
	while (curr)
	{
		// if (curr->type == OUT)
		// // {
		// // }
		// printf("[%s]\n", curr->content);
		curr = curr->next;
	}
	return (true);
}

static void	handle_command_node(t_leaf *node, t_gc **garbage)
{
	if (!node || node->type != COMMAND)
		return ;
	if (node->token && node->token->redics)
	{
		if (exec_redirec(node->token, garbage))
		{
			printf("======[TEST]======\n");
		}
	}
}

static void	traverse_child(t_leaf *child, t_gc **garbage)
{
	if (!child)
		return ;
	if (child->type == COMMAND)
		handle_command_node(child, garbage);
	else
		init_redirection(&child, garbage);
}

void	init_redirection(t_leaf **root, t_gc **garbage)
{
	t_leaf *tmp;

	if (!root || !(*root))
		return ;
	tmp = *root;
	if (tmp->type == COMMAND)
		handle_command_node(tmp, garbage);

	if (tmp->right)
		traverse_child(tmp->right, garbage);
	if (tmp->left)
		traverse_child(tmp->left, garbage);
}