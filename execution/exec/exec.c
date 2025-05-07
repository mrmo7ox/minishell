/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:11 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/07 09:15:16 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	exe_cmd_hundler(t_leaf *node, t_env **ft_env, t_gc **garbage)
{
	char	**args;

	args = NULL;
	if (node->token->token)
	{
		args = ft_args_split(node->token->token, garbage, 0, 0);
		if (!args)
		{
			exec_redirec(node->token, garbage);
			return (false);
		}
		// exec_redirec(node->token, garbage);
		exe_cmd(args, node->token, ft_env, garbage);
	}
	return (true);
}

int	execc(t_leaf **root, t_env **ft_env, t_gc **garbage)
{
	t_leaf	*node;

	if (!(*root))
		return (1);
	node = *root;
	// if (node->token->subshell > 0 == COMMAND)
	// 	return (exe_subshell(node, ft_env, garbage));
	if (node->type == COMMAND)
		return (exe_cmd_hundler(node, ft_env, garbage));
	// if (node->type == PIPE)
	// 	return (exec_pipe(node->left, node->right, garbage, ft_env));
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
