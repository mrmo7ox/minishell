/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:11 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/09 16:15:04 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	exe_cmd_hundler(t_leaf *node, int *status, t_env **ft_env, t_gc **garbage)
{
	char	**args;
	int		o[2];

	o[0] = 1;
	o[1] = 1;
	args = NULL;
	if (node->token->token)
	{
		args = ft_args_split(node->token->token, garbage, 0, 0);
		for (int i = 0; args[i]; i++)
		{
			args[i] = expander(args[i], garbage, ft_env, o);
		}
		exec_redirec(node->token, garbage, ft_env);
		exe_cmd(args, status, ft_env, garbage);
	}
	else
	{
		exec_redirec(node->token, garbage, ft_env);
		return (false);
	}
	return (true);
}

int	execc(t_leaf **root, int *status, t_env **ft_env, t_gc **garbage)
{
	t_leaf	*node;

	if (!(*root))
		return (1);
	node = *root;
	// if (node->token->subshell > 0 == COMMAND)
	// 	return (exe_subshell(node, ft_env, garbage));
	if (node->type == COMMAND)
		return (exe_cmd_hundler(node, status, ft_env, garbage));
	// if (node->type == PIPE)
	// 		return (exec_pipe(node->left, node->right, garbage, ft_env));
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
