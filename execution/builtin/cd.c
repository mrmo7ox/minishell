/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:36:13 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/09 11:21:28 by moel-oua         ###   ########.fr       */
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

static void	no_args(t_env **ft_env)
{
	char	*home;
	
	home = ft_getenv("HOME", ft_env);
	if (!home)
	{
		ft_putstr_fd("HOME not set\n", 2);
		return ;
	}
	if (chdir(home) == -1)
	perror("cd ");
}

static void	update_pwd(t_env **ft_env)
{
	if (check_name_env("PWD", ft_env))
		ft_upenv("PWD", getcwd(NULL, 0), ft_env);
	else
		ft_putenv("PWD", getcwd(NULL, 0), ft_env);
}

static int	helper(char *str, t_gc **gg, t_env **ft_env)
{
	char	*buff;

	buff = pwd();
	if (!buff)
	{
		if (chdir("/") == -1)
		{
			ft_putstr_fd("somthing went wrong\n", 2);
			return (1);
		}
	}
	buff = ft_strjoin(buff, "/", gg);
	buff = ft_strjoin(buff, str, gg);
	if (chdir(buff) == -1)
		perror("cd ");
	update_pwd(ft_env);
	return (0);
}


int	cd(char **args, t_gc **gg, t_env **ft_env)
{
	size_t	len;

	if (!args)
		return (1);
	len = args_len(args);
	if (len == 1)
		no_args(ft_env);
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
		}
		else
			return (helper(args[1], gg, ft_env));
	}
	return (0);
}
