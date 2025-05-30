/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:45 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/30 10:20:38 by ihamani          ###   ########.fr       */
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

void	no_env(t_env **ft_env, t_gc **gc)
{
	pwd_update(ft_env, 0);
	shlvl(ft_env, gc);
	ft_add_env(ft_env, ft_new_env("_", "/usr/bin/env"));
}

static bool	check_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

void	shlvl(t_env **ft_env, t_gc **gc)
{
	char	*old;
	int		lvl;

	if (check_name_env("SHLVL", ft_env))
	{
		old = ft_getenv("SHLVL", ft_env);
		if (!old || !check_valid(old))
			ft_upenv("SHLVL", "1", ft_env);
		else
		{
			lvl = ft_atoi(old);
			if (lvl++ < 999)
				ft_upenv("SHLVL", ft_itoa(lvl, gc), ft_env);
			else
			{
				ft_putstr_fd("shell level (1000) too high, resetting to 1\n",
					2);
				ft_upenv("SHLVL", "1", ft_env);
			}
		}
	}
	else
		ft_putenv("SHLVL", "1", ft_env);
}
