/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:46:28 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/07 11:30:52 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_gc(t_gc **head, t_gc *new)
{
	t_gc	*last;

	if (!head || !new)
		return ;
	last = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

void	ft_add_node(t_list **head, t_list *new)
{
	t_list	*last;

	if (!head || !new)
		return ;
	last = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

void	ft_add_tk(t_tk **head, t_tk *new)
{
	t_tk	*last;

	if (!(head) || !new)
		return ;
	if (!(*head))
	{
		(*head) = new;
		new->prev = NULL;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	ft_add_redic(t_redic **head, t_redic *new)
{
	t_redic	*last;

	if (!(head) || !new)
		return ;
	if (!(*head))
	{
		(*head) = new;
		new->prev = NULL;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}
