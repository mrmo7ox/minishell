/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:36:13 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/01 10:27:25 by ihamani          ###   ########.fr       */
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

static void	no_args(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("HOME not set\n", 2);
		return ;
	}
	if (chdir(home) == -1)
		perror("cd ");
}

static void	helper(char *str, t_gc **gg)
{
	char	*buff;
	char	*tmp;

	buff = pwd();
	if (!buff)
	{
		if (chdir("/") == -1)
			ft_putstr_fd("somthing went wrong\n", 2);
	}
	tmp = buff;
	buff = ft_strjoin(buff, "/", gg);
	free(tmp);
	tmp = buff;
	buff = ft_strjoin(buff, str, gg);
	free(tmp);
	if (chdir(buff) == -1)
		perror("cd ");
	free(buff);
}

void	cd(char **args, t_gc **gg)
{
	size_t	len;

	if (!args)
		return ;
	len = args_len(args);
	if (len == 1)
		no_args();
	else if (len > 2)
		ft_putstr_fd("too many argument\n", 2);
	else if (len == 2)
	{
		if (args[1][0] == '/')
		{
			if (chdir(args[1]) == -1)
				perror("cd ");
		}
		else
			helper(args[1], gg);
	}
}
