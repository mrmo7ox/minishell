/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:13:58 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/16 11:42:41 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cmd(t_leaf **root, t_container *c)
{
	t_leaf	*node;
	char	**args;

	node = *root;
	if (node->token->token)
	{
		args = ft_args_split(node->token->token, c->garbage, 0, 0);
		for (int i = 0; args[i]; i++)
			args[i] = expander(args[i], c);
		exec_redirec(node->token, c);
		exe_cmd(args, c);
	}
	else
	{
		exec_redirec(node->token, c);
		return ;
	}
}

void	exe_and(t_leaf **root, t_container *c)
{
	t_leaf	*node;

	node = *root;
	if (node->right->type == AND)
		exe_and(&node->right, c);
	else if (node->right->type == PIPE)
		pipe_handle(&node->right, NULL, c, 1);
	else if (node->right->type == COMMAND)
		cmd(&node->right, c);
	if (node->left->type == AND)
		exe_and(&node->left, c);
	else if (node->left->type == PIPE && c->status == 0)
		pipe_handle(&node->left, NULL, c, 1);
	else if (node->left->type == COMMAND && c->status == 0)
		cmd(&node->left, c);
}

void	exe_or(t_leaf **root, t_container *c)
{
	t_leaf	*node;

	node = *root;
	if (node->right->type == AND)
		exe_and(&node->right, c);
	else if (node->right->type == PIPE && c->status != 0)
		pipe_handle(&node->right, NULL, c, 1);
	else if (node->right->type == COMMAND)
		cmd(&node->right, c);
	if (node->left->type == AND)
		exe_and(&node->left, c);
	else if (node->left->type == PIPE && c->status != 0)
		pipe_handle(&node->left, NULL, c, 1);
	else if (node->left->type == COMMAND && c->status != 0)
		cmd(&node->left, c);
}
