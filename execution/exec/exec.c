/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:11 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 16:19:19 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	exe_cmd_hundler(t_leaf *node, t_c *c)
{
	char	**args;

	args = NULL;
	args = ft_args_split(node->token->token, c->garbage, 0, 0);
	args = expander(args, c);
	if (!args)
		return (exec_redirec(node->token, c), set_status(0, -1), true);
	args = wildcards(args, c);
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

void	init_heredoc(t_leaf **root, t_c *c)
{
	t_leaf	*tmp;

	if (!root || !*root)
		return ;
	tmp = *root;
	if (tmp->right)
		init_heredoc(&tmp->right, c);
	if (tmp->left)
		init_heredoc(&tmp->left, c);
	if (tmp->type == COMMAND)
		tmp->token->heredoc = 0;
}

int	execc(t_c *c)
{
	t_leaf	*node;
	t_leaf	**root;

	root = c->root;
	if (!(*root))
		return (1);
	node = *root;
	init_heredoc(root, c);
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
