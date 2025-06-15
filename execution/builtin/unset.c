/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:40:54 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/15 10:19:22 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	void	free_node(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

static void	remove_node(char *name, t_env **ft_env)
{
	t_env	*head;
	t_env	*prev;
	t_env	*t;

	head = *ft_env;
	prev = NULL;
	t = NULL;
	while (head && ft_strcmp(head->name, name))
	{
		prev = head;
		head = head->next;
	}
	t = head;
	if (!prev)
	{
		*ft_env = (*ft_env)->next;
		free_node(t);
	}
	else if (head)
	{
		prev->next = head->next;
		free_node(t);
	}
	else if (!head && !ft_strcmp(name, "PATH"))
		env_check_path(ft_env, -1);
}

static void	remove_path(char *name, t_env **ft_env)
{
	if (!ft_strcmp(name, "PATH"))
		env_check_path(ft_env, -1);
}

int	ft_unset(char **args, t_env **ft_env)
{
	int	i;

	i = 1;
	if (!ft_env || !*ft_env)
	{
		while (args[i])
			remove_path(args[i++], ft_env);
		return (0);
	}
	while (args[i])
	{
		if (!ft_strcmp("_", args[i]))
			i++;
		else
			remove_node(args[i++], ft_env);
	}
	return (0);
}
