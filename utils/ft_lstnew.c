/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:48:19 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/13 18:12:23 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gc	*ft_new_gc_node(void *content)
{
	t_gc *node;

	node = malloc(sizeof(t_gc));
	if(!node)
		return (NULL);
	node->addr = content;
	node->next = NULL;
	return node;
}

t_tk	*ft_new_tk_node(void *content, void *token)
{
	t_tk *node;

	node = malloc(sizeof(t_tk));
	if(!node)
		return (NULL);
	node->str = content;
	node->token = token;
	node->prev = NULL;
	node->next = NULL;
	return node;
}