/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:04:58 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/13 15:09:18 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_check_path(t_env **ft_env, int flag)
{
	static char	*path;

	if (!flag)
	{
		if (!check_name_env("PATH", ft_env))
			path = PATH;
		else
			path = NULL;
	}
	else if (flag == -1)
		path = NULL;
	else
		return (path);
	return (path);
}

void	env_init_helper(char *name, char *value, t_env **ft_env)
{
	if (!value)
		ft_add_env(ft_env, ft_new_env(name, ""));
	else
		ft_add_env(ft_env, ft_new_env(name, value));
}
