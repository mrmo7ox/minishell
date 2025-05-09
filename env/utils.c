/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:45 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/09 10:19:33 by moel-oua         ###   ########.fr       */
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
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	no_env(t_env **ft_env, t_gc **gc)
{
	ft_add_env(ft_env, ft_new_env(ft_strdupnofree("PWD"), getcwd(NULL, 0)));
	shlvl(ft_env, gc);
	ft_add_env(ft_env, ft_new_env(ft_strdupnofree("_"),
			ft_strdupnofree("/usr/bin/env")));
}

static bool	check_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '1'))
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
		if (!check_valid(old))
			ft_upenv("SHLVL", ft_strdupnofree("1"), ft_env);
		else
		{
			lvl = ft_atoi(old);
			lvl++;
			ft_upenv("SHLVL", ft_strdupnofree(ft_itoa(lvl, gc)), ft_env);
		}
	}
	else
		ft_putenv("SHLVL", "1", ft_env);
}
