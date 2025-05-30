/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:15:33 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 16:51:26 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	get_precedence(t_type type)
{
	if (type == OR)
		return (1);
	if (type == AND)
		return (2);
	if (type == PIPE)
		return (3);
	return (4);
}
void	insert_node(t_leaf **root, t_leaf *new_node)
{
	t_leaf	*curr;

	if (!*root)
	{
		*root = new_node;
		return ;
	}
	if (get_precedence(new_node->type) > get_precedence((*root)->type)
		|| new_node->token->subshell != (*root)->token->subshell)
	{
		curr = *root;
		while (curr->right
			&& get_precedence(new_node->type) > get_precedence(curr->right->type)
			&& new_node->token->subshell == curr->right->token->subshell)
		{
			curr = curr->right;
		}
		new_node->left = curr->right;
		curr->right = new_node;
	}
	else
	{
		new_node->left = *root;
		*root = new_node;
	}
}

t_leaf	*build_ast_for_subshell(t_tk **tokens, int current_subshell,
		t_gc **garbage)
{
	t_leaf	*root;
	t_leaf	*subtree;

	root = NULL;
	while (*tokens)
	{
		if ((*tokens)->subshell < current_subshell)
			break ;
		if ((*tokens)->subshell > current_subshell)
		{
			subtree = build_ast_for_subshell(tokens, (*tokens)->subshell,
					garbage);
			if (!subtree)
				return (NULL);
			insert_node(&root, subtree);
		}
		else
		{
			subtree = new_leaf(*tokens, (*tokens)->type, garbage);
			if (!subtree)
				return (NULL);
			insert_node(&root, subtree);
			*tokens = (*tokens)->next;
		}
	}
	return (root);
}

t_tk	*reverse_tokens(t_tk *head)
{
	t_tk	*prev;
	t_tk	*curr;
	t_tk	*next;

	prev = NULL;
	curr = head;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return (prev);
}

t_leaf	*build_ast(t_tk *tokens, t_gc **garbage)
{
	t_leaf	*root;

	root = NULL;
	root = build_ast_for_subshell(&tokens, 0, garbage);
	return (root);
}
