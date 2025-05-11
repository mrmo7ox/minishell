/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:11:44 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/11 10:01:01 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*pwd_update(t_env **ft_env, int flag)
{
	static char	*old;
	char		*tmp;

	if (!flag)
	{
		tmp = old;
		old = getcwd(NULL, 0);
		if (!old)
			old = tmp;
		else
			free(tmp);
		if (check_name_env("PWD", ft_env))
			ft_upenv("PWD", old, ft_env);
		else
			ft_putenv("PWD", old, ft_env);
	}
	else if (flag == 1)
	{
		free(old);
		old = NULL;
	}
	return (old);
}

int	ft_pwd(t_env **ft_env, int out)
{
	if (!out)
		out = 1;
	ft_putstr_fd(pwd_update(ft_env, 0), out);
	ft_putstr_fd("\n", out);
	return (0);
}
