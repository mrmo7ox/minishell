/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:11 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/13 15:12:46 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	exe_cmd_hundler(t_leaf *node, t_container *c)
{
	char	**args;

	args = NULL;
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
		return (false);
	}
	return (true);
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

int execc(t_container *c)
{
	t_leaf	*node;
	t_leaf	**root;

	root = c->root;
	if (!(*root))
		return (1);
	node = *root;
	// print_ast(node, 0);
	// if (node->token->subshell > 0 == COMMAND)
	// 	return (exe_subshell(node, ft_env, garbage));
	// print_ast(node, "O", 0);
	if (node->type == COMMAND)
		return (exe_cmd_hundler(node, c));
	if (node->type == PIPE)
		pipe_handle(root, NULL, c, 1);
	// if (node->type == AND)
	// {
	// 	if (exec(node->left, ft_env, garbage) == 0)
	// 		return (exec(node->right, ft_env, garbage));
	// }
	// if (node->type == OR)
	// {
	// 	if (exec_pipe(node->left) != 0)
	// 		return (exec_pipe(node->right));
	// 	return (0);
	// }
	return (1);
}
