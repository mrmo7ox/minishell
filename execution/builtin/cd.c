/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:36:13 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/30 16:17:44 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (NULL);
	return (buff);
}

static int	no_args(t_env **ft_env)
{
	char	*home;

	home = ft_getenv("HOME", ft_env);
	if (!home)
	{
		ft_putstr_fd("HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return (1);
	}
	pwd_update(ft_env, 0);
	return (0);
}

static int	helper(char *str, t_gc **gg, t_env **ft_env)
{
	char	*buff;
	char	*tmp;

	buff = pwd();
	if (!buff)
	{
		if (chdir("/") == -1)
		{
			ft_putstr_fd("somthing went wrong\n", 2);
			return (1);
		}
		pwd_update(ft_env, 0);
	}
	else
	{
		tmp = buff;
		buff = ft_strjoin(buff, "/", gg);
		free(tmp);
		buff = ft_strjoin(buff, str, gg);
		if (chdir(buff) == -1)
			return (perror("cd "), 1);
		pwd_update(ft_env, 0);
	}
	return (0);
}

int	cd(char **args, t_gc **gg, t_env **ft_env)
{
	size_t	len;

	if (!args)
		return (1);
	len = args_len(args);
	if (len == 1)
		return (no_args(ft_env));
	else if (len > 2)
	{
		ft_putstr_fd("too many argument\n", 2);
		return (1);
	}
	else if (len == 2)
	{
		if (args[1][0] == '/')
		{
			if (chdir(args[1]) == -1)
				return (perror("cd "), 1);
			pwd_update(ft_env, 0);
		}
		else
			return (helper(args[1], gg, ft_env));
	}
	return (0);
}
