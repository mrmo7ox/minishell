/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:11 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/12 10:29:17 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool exe_cmd_hundler(t_leaf *node, t_container *c)
{
	char **args;

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


int execc(t_container *c)
{
	t_leaf	*node;
	t_leaf	**root;
	t_pipe	pip;
	t_pipe	*tmp;

	root = c->root;
	if (!(*root))
		return (1);
	node = *root;
	// print_ast(node, 0);
	// if (node->token->subshell > 0 == COMMAND)
	// 	return (exe_subshell(node, ft_env, garbage));
	if (node->type == COMMAND)
		return (exe_cmd_hundler(node, c));
	if (node->type == PIPE)
	{
		pipe_handle(root, &pip, c, 1);
		pid_wait(pip.lst, c);
	}
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
