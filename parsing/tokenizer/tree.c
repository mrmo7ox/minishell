/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:15:33 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/29 10:44:07 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_tree(t_leaf *node, int depth, int is_left)
{
	t_redic	*current;

	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("    ");
	if (depth > 0)
		printf("%s── ", is_left ? "┌" : "└");
	printf("[%s]", node->token->token);
	current = node->token->redics;
	while (current)
	{
		printf("{%s}", current->content);
		current = current->next;
	}
	printf("\n");
	if (node->left)
	{
		for (int i = 0; i < depth; i++)
			printf("    ");
		printf("    \n");
		print_tree(node->left, depth + 1, 1);
	}
	if (node->right)
	{
		for (int i = 0; i < depth; i++)
			printf("    ");
		printf("    \n");
		print_tree(node->right, depth + 1, 0);
	}
}

void	add_cmd(t_leaf *cmd_leaf, t_leaf **root)
{
	t_leaf	*temp;

	if (!(*root))
		(*root) = cmd_leaf;
	else
	{
		temp = (*root);
		while (temp->right)
			temp = temp->right;
		temp->right = cmd_leaf;
	}
}

void	add_op(t_leaf *op_leaf, t_leaf **root)
{
	if (!(*root))
		(*root) = op_leaf;
	else
	{
		op_leaf->left = (*root);
		(*root) = op_leaf;
	}
}

t_leaf	*make_tree(t_tk *tokens, t_gc **garbage)
{
	t_leaf	*root;
	t_tk	*current;

	if (!tokens)
		return (NULL);
	root = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == COMMAND)
		{
			add_cmd(new_leaf(current, COMMAND, garbage), &root);
		}
		else
			add_op(new_leaf(current, OPERATOR, garbage), &root);
		current = current->next;
	}
	return (root);
}

t_leaf	*new_leaf(t_tk *token, t_type type, t_gc **garbage)
{
	t_leaf	*new;

	new = ft_malloc(sizeof(t_leaf), garbage);
	if (!new)
		return (NULL);
	new->type = type;
	new->token = token;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
