/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:11 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/02 13:23:37 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	exe_cmd_hundler(t_leaf *node, t_c *c)
{
	char	**args;

	args = NULL;
	if (node->token->token)
	{
		args = ft_args_split(node->token->token, c->garbage);
		args = expander(args, c);
	}
	if (!args)
	{
		exec_redirec(node->token, c);
		if (node->token->in == -1 || node->token->out == -1)
			return (true);
		close_redr(&node);
		return (set_status(0, -1), true);
	}
	exe_cmd(args, c);
	return (true);
}

void	run_heredoc(t_leaf **root, t_c *c)
{
	t_leaf	*tmp;

	if (!root || !*root)
		return ;
	tmp = *root;
	if (tmp->right)
		run_heredoc(&tmp->right, c);
	if (tmp->left)
		run_heredoc(&tmp->left, c);
	if (tmp->type == COMMAND)
		exec_heredoc(tmp->token, c);
}

void	close_heredoc(t_leaf **root, t_c *c)
{
	t_leaf	*tmp;

	if (!root || !*root)
		return ;
	tmp = *root;
	if (tmp->right)
		close_heredoc(&tmp->right, c);
	if (tmp->left)
		close_heredoc(&tmp->left, c);
	if (tmp->type == COMMAND)
	{
		if (tmp->token->heredoc > 0)
		{
			close(tmp->token->heredoc);
			tmp->token->heredoc = 0;
		}
	}
}

void	init_redr(t_leaf **root, t_c *c)
{
	t_leaf	*tmp;

	if (!root || !*root)
		return ;
	tmp = *root;
	if (tmp->right)
		init_redr(&tmp->right, c);
	if (tmp->left)
		init_redr(&tmp->left, c);
	if (tmp->type == COMMAND)
	{
		tmp->token->heredoc = 0;
		tmp->token->in = 0;
		tmp->token->out = 0;
	}
}

int	execc(t_c *c)
{
	t_leaf	*node;
	t_leaf	**root;

	root = c->root;
	if (!(*root))
		return (1);
	node = *root;
	init_redr(root, c);
	run_heredoc(root, c);
	if (g_signal != 169)
	{
		if (node->type == PIPE)
			pipe_handle(root, NULL, c, 1);
		else if (node->type == COMMAND)
			return (exe_cmd_hundler(node, c));
	}
	return (1);
}
