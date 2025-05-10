/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:48:19 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/09 20:45:54 by moel-oua         ###   ########.fr       */
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

t_qoutes	*ft_new_node(int open, int close, t_qtype type, t_gc **garbage)
{
	t_qoutes	*node;

	node = ft_malloc(sizeof(t_qoutes), garbage);
	if (!node)
		return (NULL);
	node->open_index = open;
	node->close_index = close;
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_expand	*ft_new_expand(int start, int end, bool expand, t_gc **garbage)
{
	t_expand	*node;

	node = ft_malloc(sizeof(t_expand), garbage);
	if (!node)
		return (NULL);
	node->start = start;
	node->end = end;
	node->expand = expand;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_tk	*ft_new_tk_node(char *content, t_gc **garbage, t_split_utils *utils)
{
	t_tk	*node;

	node = ft_malloc(sizeof(t_tk), garbage);
	if (!node)
		return (NULL);
	node->token = formating(content, garbage);
	node->priority = utils->priority;
	node->index = utils->index;
	node->type = utils->type;
	node->subshell = utils->subshell;
	node->prev = NULL;
	node->next = NULL;
	node->redics = NULL;
	return (node);
}

void	*ft_new_redic_node(t_gc **garbage, char *content)
{
	t_redic	*node;

	node = ft_malloc(sizeof(t_redic), garbage);
	if (!node)
		return (NULL);
	node->content = formating(content, garbage);
	node->type = special_cases_redic(content);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_pipe	*new_pip(int fd, int status, t_gc **gc)
{
	t_pipe	*new;

	new = ft_malloc(sizeof(t_pipe), gc);
	new->fd = fd;
	new->status = status;
	return (new);
}
