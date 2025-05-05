/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:40:54 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/04 12:29:20 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	remove_node(char *name, t_env **ft_env)
{
	t_env	*head;
	t_env	*prev;

	head = *ft_env;
	prev = NULL;
	while (head && ft_strcmp(head->name, name))
	{
		prev = head;
		head = head->next;
	}
	if (!prev)
		*ft_env = (*ft_env)->next;
	else if (head)
		prev->next = head->next;
}

void	ft_unset(char **args, t_env **ft_env)
{
	int	i;

	i = 1;
	while (args[i])
		remove_node(args[i++], ft_env);
}
