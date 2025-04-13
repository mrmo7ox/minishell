/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:15:33 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/13 15:20:56 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*ft_newtree(char **content)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	ft_minisplit(content[0], ' ', 0, 0);
	node->content = content;
	node->priority = 0;
	node->left = NULL;
	node->right = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_addtree_node(t_node **node, t_node *left, t_node *right)
{
	if (!node || !(*node))
		return ;
	(*node)->left = left;
	(*node)->right = right;
	
	if (left)
        left->prev = (*node);
    if (right)
        right->prev = (*node);
}
