/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:51:05 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/29 13:25:54 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*helper(char *name, t_gc **gc)
{
	char	*new;

	new = ft_substr(name, 0, ft_strlen(name) - 1, gc);
	return (new);
}

void	export_append(char *name, char *value, t_env **ft_env, t_gc **gg)
{
	char	*tmp;
	t_env	*head;

	(void)gg;
	name = helper(name, gg);
	head = *ft_env;
	while (head && ft_strcmp(name, head->name))
		head = head->next;
	if (head)
	{
		tmp = head->value;
		head->value = ft_strdupnofree(ft_strjoin(head->value, value, gg));
		free(tmp);
	}
	else
		ft_putenv(name, value, ft_env);
}

void	ft_upenv(char *name, char *value, t_env **ft_env)
{
	char	*tmp;
	t_env	*head;

	head = *ft_env;
	while (head && ft_strcmp(name, head->name))
		head = head->next;
	if (head && value)
	{
		tmp = head->value;
		head->value = ft_strdupnofree(value);
		free(tmp);
	}
}

static int	check_key(char *str, char *value)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (i == 0 && ((str[i] >= '0' && str[i] <= '9')
				|| str[i] == '+'))
			return (0);
		if (ft_chrstr(str[i], "-!?$%@-#/\\"))
			return (0);
		if (str[i] == '+' && str[i + 1])
			return (0);
		if (str[i] == '+' && !str[i + 1] && value)
			return (2);
		if (str[i] == '+' && !str[i + 1] && !value)
			return (0);
		i++;
	}
	return (1);
}

int	ext_export(char *name, char *value, t_env **ft_env, t_gc **gg)
{
	if (!ft_strcmp(name, "_"))
		return (1);
	if (!check_key(name, value))
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	else if (check_key(name, value) == 2)
		export_append(name, value, ft_env, gg);
	else
	{
		if (!check_name_env(name, ft_env))
		{
			if (!ft_strcmp(name, "PATH") && value == NULL)
				ft_putenv(name, env_check_path(ft_env, 2), ft_env);
			else
				ft_putenv(name, value, ft_env);
		}
		else
			ft_upenv(name, value, ft_env);
	}
	return (0);
}
