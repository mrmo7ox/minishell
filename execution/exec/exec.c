/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:11 by moel-oua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/25 10:43:23 by moel-oua         ###   ########.fr       */
=======
/*   Updated: 2025/05/26 15:29:09 by ihamani          ###   ########.fr       */
>>>>>>> b83c7b127b5818736ba53aeb657be28f02e8c38b
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	exe_cmd_hundler(t_leaf *node, t_container *c)
{
	char	**args;
	int		i;

	i = 0;
	args = NULL;
	if (node->token->token)
	{
		args = ft_args_split(node->token->token, c->garbage, 0, 0);
		args = expander(args, c);
		exe_cmd(args, c);
	}
	else
		return (false);
	return (true);
}

void	run_heredoc(t_leaf **root, t_container *c)
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

void	close_heredoc(t_leaf **root, t_container *c)
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
			close(tmp->token->heredoc);
	}
}
// void	print_node(t_leaf *node, char *l)
// {
// 	if (!node || !node->token)
// 		return ;
// 	printf("[%s]", l);
// 	if (node->type == AND)
// 		printf("Operator: &&\n");
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

int	execc(t_container *c)
{
	t_leaf	*node;
	t_leaf	**root;

	root = c->root;
	if (!(*root))
		return (1);
	node = *root;
	// if (node->token->subshell > 0 == COMMAND)
	// 	return (exe_subshell(node, ft_env, garbage));
	// print_ast(node, "O", 0);
	run_heredoc(root, c);
	if (node->type == OR)
		exe_or(root, c);
	else if (node->type == AND)
		exe_and(root, c);
	else if (node->type == PIPE)
		pipe_handle(root, NULL, c, 1);
	else if (node->type == COMMAND)
		return (exe_cmd_hundler(node, c));
	return (1);
}
