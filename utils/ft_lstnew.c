/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:48:19 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/16 13:21:29 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gc	*ft_new_gc_node(void *content)
{
	t_gc	*node;

	node = malloc(sizeof(t_gc));
	if (!node)
		return (NULL);
	node->addr = content;
	node->next = NULL;
	return (node);
}

t_tk	*ft_new_tk_node(char *content, int priority, t_gc **garbage, int index)
{
	t_tk	*node;
	
	node = malloc(sizeof(t_tk));
	if (!node)
		return (NULL);
	node->token = formating(content, garbage);
	node->priority = priority;
	node->index= index;
	if (special_cases(content))
		node->op = ft_strdup("O");
	else
		node->op = ft_strdup("C");
		
	node->prev = NULL;
	node->next = NULL;

	return (node);
}

t_ready	*ft_new_ready(char **content, int priority, t_gc **garbage)
{
	t_ready	*node;
	
	node = malloc(sizeof(t_tk));
	ft_add_gc(garbage,ft_new_gc_node(node));
	if (!node)
		return (NULL);
	node->tokens = content;
	node->priority = priority;		
	node->prev = NULL;
	node->next = NULL;

	return (node);
}

t_redirections	*ft_new_redirection(char *content, char *op , int team)
{
	t_redirections	*node;
	
	node = malloc(sizeof(t_tk));
	if (!node)
		return (NULL);
	node->content = content;
	node->op = op;
	node->index = team;		
	node->prev = NULL;
	node->next = NULL;

	return (node);
}
