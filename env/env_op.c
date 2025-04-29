/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:50:48 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/29 13:20:39 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_init(char **env, t_env **ft_env, t_gc **gc)
{
	int		i;
	char	**tmp;

	i = 0;
	while (env[i])
	{
		tmp = export_split(env[i], gc);
		if (!tmp)
			return ;
		ft_add_env(ft_env, ft_new_env(tmp[0], tmp[1]));
		free(tmp);
		i++;
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
	{
		head = head->next;
	}
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

// char    *ft_getenv(char *name, t_env **ft_env)
// {
//     t_env *head;

//     head = *ft_env;
//     while (head->next && strcmp(name, head->name))
//         head = head->next;
// 	if (head->value)
//     	return (head->value);
// 	return (NULL);
// }
