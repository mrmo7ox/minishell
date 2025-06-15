/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:11:44 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/14 14:59:19 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	old_pwd(char *old, t_env **ft_env)
{
	if (check_name_env("OLDPWD", ft_env))
	{
		if (old)
			ft_upenv("OLDPWD", old, ft_env);
		else
		{
			if (check_name_env("PWD", ft_env))
				ft_upenv("OLDPWD", ft_getenv("PWD", ft_env), ft_env);
		}
	}
}

static void	helper(t_env **ft_env, char **old)
{
	char	*tmp;

	tmp = *old;
	*old = getcwd(NULL, 0);
	if (!*old)
		*old = tmp;
	else
		free(tmp);
	if (check_name_env("PWD", ft_env))
		ft_upenv("PWD", *old, ft_env);
}

char	*pwd_update(t_env **ft_env, int flag)
{
	static char	*old;
	char		*tmp;

	if (!flag)
	{
		tmp = old;
		old_pwd(tmp, ft_env);
		old = getcwd(NULL, 0);
		if (!old)
			old = tmp;
		else
			free(tmp);
		if (check_name_env("PWD", ft_env))
			ft_upenv("PWD", old, ft_env);
	}
	else if (flag == 2)
		helper(ft_env, &old);
	else if (flag == 1)
	{
		free(old);
		old = NULL;
	}
	return (old);
}

void	init_pwd(t_env **ft_env)
{
	char	*tmp;

	if (!check_name_env("OLDPWD", ft_env))
		ft_putenv("OLDPWD", NULL, ft_env);
	tmp = getcwd(NULL, 0);
	if (!check_name_env("PWD", ft_env))
		ft_putenv("PWD", tmp, ft_env);
	else
	{
		if (tmp)
			ft_upenv("PWD", tmp, ft_env);
	}
	free(tmp);
}

int	ft_pwd(t_env **ft_env, int out)
{
	if (out == 0)
		out = 1;
	else if (out < 0)
		return (1);
	ft_putstr_fd(pwd_update(ft_env, 2), out);
	ft_putstr_fd("\n", out);
	return (0);
}
