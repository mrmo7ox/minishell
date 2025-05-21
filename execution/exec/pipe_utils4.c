/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:23:52 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/21 11:24:43 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exe_builtin_pipe(char **args, t_leaf *root, t_container *c)
{
	if (!ft_strcmp(args[0], "env"))
		return (cmd_env(args, 0, c->ft_env));
	else if (!ft_strcmp(args[0], "export"))
		export(args, 0, c->ft_env, c->garbage);
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(c->ft_env, 0));
	else if (!ft_strcmp(args[0], "echo"))
		return (echo(args, 0));
	else if (!ft_strcmp(args[0], "cd"))
		return (cd(args, c->garbage, c->ft_env));
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, c->ft_env));
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, c->ft_env, c->garbage, c->status));
	return (0);
}
