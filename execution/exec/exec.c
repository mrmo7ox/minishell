/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:11 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 11:13:55 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	exe_cmd_hundler(t_leaf *node, t_c *c)
{
	char	**args;

	args = NULL;
	args = ft_args_split(node->token->token, c->garbage, 0, 0);
	args = expander(args, c);
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

<<<<<<< HEAD
int	execc(t_container *c)
=======
// void	print_node(t_leaf *node, char *l)
// {
// 	if (!node || !node->token)
// 		return ;
// 	printf("[%s]", l);
// 	if (node->type == AND)
// 		printf("Operator: &&, %d\n,", node->token->subshell);
// 	else if (node->type == OR)
// 		printf("Operator: ||\n");
// 	else if (node->type == PIPE)
// 		printf("Operator: |\n");
// 	else
// 		printf("Command: %s\n", node->token->token);
// }

// void print_ast(t_leaf *root, char *l, int depth)
// {
// 	if (!root)
// 		return ;

// 	for (int i = 0; i < depth; i++)
// 		printf("  ");

// 	print_node(root, l);

// 	print_ast(root->left, "left", depth + 1);
// 	print_ast(root->right, "right", depth + 1);

// }

int	execc(t_c *c)
>>>>>>> cfbfeffc3d2a90ffe4e60564d7ac366060c0cf23
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
