/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:48 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/09 18:12:35 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_init(char **env, t_env **ft_env, t_gc **gc)
{
	int		i;
	char	**tmp;

	if (!(*env))
		no_env(ft_env, gc);
	else
	{
		i = 0;
		while (env[i])
		{
			tmp = export_split(env[i]);
			if (!tmp)
				return ;
			ft_add_env(ft_env, ft_new_env(tmp[0], tmp[1]));
			free(tmp[0]);
			free(tmp[1]);
			free(tmp);
			i++;
		}
		shlvl(ft_env, gc);
	}
}

void	ft_putenv(char *name, char *value, t_env **ft_env)
{
	ft_add_env(ft_env, ft_new_env(name, value));
}

char	*ft_getenv(char *name, t_env **ft_env)
{
	t_env	*head;

	head = *ft_env;
	while (head && ft_strcmp(name, head->name))
		head = head->next;
	if (head)
	{
		if (head->value)
			return (head->value);
	}
	return (NULL);
}

bool	check_name_env(char *name, t_env **ft_env)
{
	t_env	*head;

	head = *ft_env;
	while (head && ft_strcmp(name, head->name))
		head = head->next;
	if (head)
	{
		if (head->name)
			return (true);
	}
	return (false);
}

void	ft_free_env(t_env **ft_env)
{
	t_env	*tmp;
	void	*next;

	if (!*ft_env || !ft_env)
		return ;
	tmp = *ft_env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*ft_env = NULL;
}
