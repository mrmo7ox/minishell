/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:15:33 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 15:04:56 by moel-oua         ###   ########.fr       */
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

void	insert_node(t_leaf **root, t_tk *token, t_gc **garbage)
{
	t_leaf	*new;
	t_leaf	*curr;

	new = new_leaf(token, token->type, garbage);
	if (!*root)
	{
		*root = new;
		return ;
	}
	if (get_precedence(token->type) < get_precedence((*root)->type))
	{
		new->left = *root;
		*root = new;
	}
	else
	{
		curr = *root;
		while (curr->right
			&& get_precedence(token->type) >= get_precedence(curr->right->type))
			curr = curr->right;
		new->left = curr->right;
		curr->right = new;
	}
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
	tokens = reverse_tokens(tokens);
	while (tokens)
	{
		insert_node(&root, tokens, garbage);
		tokens = tokens->next;
	}
	return (root);
}
