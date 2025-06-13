/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:09:05 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/31 17:43:01 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_builtin(char *str)
{
	if (!ft_strcmp(str, "env"))
		return (true);
	else if (!ft_strcmp(str, "export"))
		return (true);
	else if (!ft_strcmp(str, "pwd"))
		return (true);
	else if (!ft_strcmp(str, "echo"))
		return (true);
	else if (!ft_strcmp(str, "cd"))
		return (true);
	else if (!ft_strcmp(str, "unset"))
		return (true);
	else if (!ft_strcmp(str, "exit"))
		return (true);
	else
		return (false);
}

int	exe_builtin(char **args, t_leaf *root, t_c *c)
{
	exec_redirec(root->token, c);
	if (root->token->in == -1 || root->token->out == -1)
		return (1);
	if (!ft_strcmp(args[0], "env"))
		return (cmd_env(args, root->token->out, c->ft_env));
	else if (!ft_strcmp(args[0], "export"))
		return (export(args, root->token->out, c->ft_env, c->garbage));
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(c->ft_env, root->token->out));
	else if (!ft_strcmp(args[0], "echo"))
		return (echo(args, root->token->out));
	else if (!ft_strcmp(args[0], "cd"))
		return (cd(args, c->garbage, c->ft_env));
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, c->ft_env));
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, c->ft_env, c->garbage, set_status(0, 0)));
	close_redr(&root);
	return (0);
}

void	exit_exe(t_env **ft_env, t_gc **gc, int err)
{
	(void)ft_env;
	free_garbage(gc);
	exit(err);
}

char	*get_path(char **args, t_env **ft_env, t_gc **gc)
{
	char	*path;
	char	**paths;
	char	*cmd;
	int		i;

	path = ft_strdup(ft_getenv("PATH", ft_env), gc);
	if (!path || !path[0])
	{
		path = env_check_path(ft_env, 2);
		if (!path)
			return (ft_strdup(args[0], gc));
	}
	cmd = ft_strjoin("/", args[0], gc);
	paths = ft_vanilla_split(path, ':', 0, 0);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd, gc);
		if (!access(path, X_OK))
			return (path);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (NULL);
}

void	redr_cmd(t_leaf *tmp, t_c *c)
{
	if (tmp->token->in > 0)
	{
		if (dup2(tmp->token->in, 0) == -1)
		{
			perror("dup2");
			close_redr(&tmp);
			exit_exe(c->ft_env, c->garbage, 1);
		}
		close(tmp->token->in);
	}
	else if (tmp->token->in < 0)
		redr_cmd_helper(tmp, c);
	if (tmp->token->out > 0)
	{
		if (dup2(tmp->token->out, 1) == -1)
		{
			perror("dup2");
			close_redr(&tmp);
			exit_exe(c->ft_env, c->garbage, 1);
		}
		close(tmp->token->out);
	}
	else if (tmp->token->out < 0)
		redr_cmd_helper(tmp, c);
}
