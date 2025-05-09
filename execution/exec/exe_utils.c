/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:09:05 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/09 11:08:06 by moel-oua         ###   ########.fr       */
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

int	exe_builtin(char **args, t_env **ft_env, t_gc **gc)
{
	if (!ft_strcmp(args[0], "env"))
		return (cmd_env(args, ft_env));
	else if (!ft_strcmp(args[0], "export"))
		export(args, ft_env, gc);
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(args, gc));
	else if (!ft_strcmp(args[0], "echo"))
		return (echo(args));
	else if (!ft_strcmp(args[0], "cd"))
		return (cd(args, gc, ft_env));
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, ft_env));
	else if (!ft_strcmp(args[0], "exit"))
	{
		ft_free_env(ft_env);
		exit(0);
	}
	return (0);
}

void	exit_exe(t_env **ft_env, t_gc **gc, int err)
{
	(void)ft_env;
	// ft_free_env(ft_env);
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
	if (!path)
		return (ft_strdup(args[0], gc));
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
