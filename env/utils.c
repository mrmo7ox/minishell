/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:45 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/13 14:07:02 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_env(t_env **head, t_env *new)
{
	t_env	*last;

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

t_env	*ft_new_env(char *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		perror("malloc");
		exit(1);
	}
	node->name = ft_strdupnofree(name);
	node->value = ft_strdupnofree(value);
	node->next = NULL;
	return (node);
}

void	no_env(t_env **ft_env)
{
	init_pwd(ft_env);
	ft_add_env(ft_env, ft_new_env("_", "/usr/bin/env"));
}
