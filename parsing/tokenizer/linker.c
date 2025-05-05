/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:26:19 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/04 14:36:19 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_command_node(t_leaf *node, void (*applyme)(t_tk *, t_gc **,
			t_env **), t_gc **garbage, t_env **ft_env)
{
	if (!node || node->type != COMMAND)
		return ;
	if (node->token && ft_strinstr(node->token->token, "$"))
		applyme(node->token, garbage, ft_env);
}

static void	traverse_child(t_leaf *child, void (*applyme)(t_tk *, t_gc **,
			t_env **), t_gc **garbage, t_env **ft_env)
{
	if (!child)
		return ;
	if (child->type == COMMAND)
		handle_command_node(child, applyme, garbage, ft_env);
	else
		linker(&child, applyme, garbage, ft_env);
}

void	linker(t_leaf **root, void (*applyme)(t_tk *, t_gc **, t_env **),
		t_gc **garbage, t_env **ft_env)
{
	t_leaf	*tmp;

	if (!root || !(*root))
		return ;
	tmp = *root;
	if (tmp->type == COMMAND)
		applyme(tmp->token, garbage, ft_env);
	traverse_child(tmp->right, applyme, garbage, ft_env);
	traverse_child(tmp->left, applyme, garbage, ft_env);
}
