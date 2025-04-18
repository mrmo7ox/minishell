/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:46:28 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/16 13:16:49 by moel-oua         ###   ########.fr       */
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

void	ft_add_tk(t_tk **head, t_tk *new)
{
	t_tk	*last;

	if (!(head) || !new)
		return ;
	if(!(*head))
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

void	ft_add_ready(t_ready **head, t_ready *new)
{
	t_ready	*last;

	if (!(head) || !new)
		return ;
	if(!(*head))
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
void	ft_add_t_redirections(t_redirections **head, t_redirections *new)
{
	t_redirections	*last;

	if (!(head) || !new)
		return ;
	if(!(*head))
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
