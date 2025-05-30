/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:45 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 17:08:02 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add_wild(t_wild **head, t_wild *new)
{
	t_wild	*last;

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

t_wild	*ft_new_wild(char *arg, t_c *c)
{
	t_wild	*node;

	node = ft_malloc(sizeof(t_wild), c->garbage);
	if (!node)
		return (NULL);
	node->arg = arg;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	ft_wildsize(t_wild *head)
{
	int	i;

	if (!head)
		return (0);
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}