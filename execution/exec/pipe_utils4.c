/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:23:52 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/31 21:04:54 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exe_builtin_pipe(char **args, t_c *c)
{
	if (!ft_strcmp(args[0], "env"))
		return (cmd_env(args, 0, c->ft_env));
	else if (!ft_strcmp(args[0], "export"))
		return (export(args, 0, c->ft_env, c->garbage));
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(c->ft_env, 0));
	else if (!ft_strcmp(args[0], "echo"))
		return (echo(args, 0));
	else if (!ft_strcmp(args[0], "cd"))
		return (cd(args, c->garbage, c->ft_env));
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, c->ft_env));
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, c->ft_env, c->garbage, set_status(c->status, 0)));
	return (0);
}

void	close_fds(t_leaf *tmp, int *fds, int *p_fd)
{
	if (fds)
	{
		close(fds[0]);
		close(fds[1]);
	}
	if (p_fd)
	{
		close(p_fd[0]);
		close(p_fd[1]);
	}
	close_redr(&tmp);
}

void	redr_cmd_helper(t_leaf *tmp, t_c *c)
{
	close_redr(&tmp);
	exit_exe(c->ft_env, c->garbage, set_status(0, 0));
}

void	child2_pipe(t_leaf *tmp, t_c *c, int *fds, int *p_fd)
{
	if (dup2(p_fd[1], 1) == -1)
	{
		perror("dup2");
		close_fds(tmp, fds, p_fd);
		close_heredoc(c->root, c);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	if (dup2(fds[0], 0) == -1)
	{
		perror("dup2");
		close_fds(tmp, fds, p_fd);
		close_heredoc(c->root, c);
		exit_exe(c->ft_env, c->garbage, 1);
	}
}

void	path_check_pro(char **args)
{
	if (ft_chrstr('/', args[0]))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
}
