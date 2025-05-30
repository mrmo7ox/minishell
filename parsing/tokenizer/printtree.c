/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printtree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:00:02 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 11:48:11 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_tree_recursively(t_leaf *node, int depth, char *direction)
{
	if (node == NULL)
		return ;
	for (int i = 0; i < depth; i++)
		printf("   ");
	printf("%s (%s)\n", node->token->token, direction);
	depth = depth + 1;
	print_tree_recursively(node->left, depth, "left");
	print_tree_recursively(node->right, depth, "right");
}

void	print_tree(t_leaf *root)
{
	if (root == NULL)
	{
		printf("Tree is empty\n");
		return ;
	}
	print_tree_recursively(root, 0, "root");
}
