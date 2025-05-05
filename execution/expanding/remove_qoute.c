/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/05 19:01:22 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_command_node(t_leaf *node, t_gc **garbage)
{
	if (!node || node->type != COMMAND)
		return ;
	if (node->token)
	{
		node->token->token = remove_qoutes(node->token->token, garbage);
	}
}

static void	traverse_child(t_leaf *child, t_gc **garbage)
{
	if (!child)
		return ;
	if (child->type == COMMAND)
		handle_command_node(child, garbage);
	else
		remove_qoutes_tree(&child, garbage);
}

void	remove_qoutes_tree(t_leaf **root, t_gc **garbage)
{
	t_leaf	*tmp;

	if (!root || !(*root))
		return ;
	tmp = *root;
	if (tmp->type == COMMAND)
		handle_command_node(tmp, garbage);
	if (tmp->right)
		traverse_child(tmp->right, garbage);
	if (tmp->left)
		traverse_child(tmp->left, garbage);
}

static void	add_to_res(t_expander *u, t_gc **garbage)
{
	char	*new;

	if (u->start < u->i)
	{
		new = ft_copy(u->line + u->start, u->i - u->start, garbage);
		if (u->double_open == 1)
			new = ft_strip('"', new, garbage);
		else if (u->double_open == 2)
			new = ft_strip('\'', new, garbage);
		u->double_open = 0;
		u->result = ft_strjoin(u->result, new, garbage);
		u->start = u->i;
	}
}

char	*remove_qoutes(char *line, t_gc **garbage)
{
	t_expander	u;
	char		quote;

	u.i = 0;
	u.start = 0;
	u.line = line;
	u.result = NULL;
	u.double_open = 0;
	while (u.line[u.i])
	{
		if (u.line[u.i] == '\"' || u.line[u.i] == '\'')
		{
			add_to_res(&u, garbage);
			quote = u.line[u.i];
			u.i++;
			u.start = u.i;
			while (u.line[u.i] && u.line[u.i] != quote)
				u.i++;
			u.double_open = (quote == '\"') ? 1 : 2;
			add_to_res(&u, garbage);
			if (u.line[u.i] == quote)
				u.i++;
			u.start = u.i;
		}
		else
			u.i++;
	}
	add_to_res(&u, garbage);
	printf("[%s]\n", u.result);
	return (u.result);
}
