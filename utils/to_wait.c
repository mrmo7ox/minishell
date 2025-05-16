/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/16 10:57:43 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.c"

t_wait	*ft_new_wait(pid_t pid, t_gc **gc)
{
	t_wait	*node;

    node = ft_malloc(sizeof(t_wait), gc);
	if (!node)
		return (NULL);
	node->pid = pid;
	node->next = NULL;
	return (node);
}

void	ft_add_wait(t_wait **head, t_wait *new)
{
	t_wait	*last;

	if (!(head) || !new)
		return ;
	if (!(*head))
	{
		(*head) = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}
