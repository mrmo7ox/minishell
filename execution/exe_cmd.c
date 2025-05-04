/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:02:42 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/04 10:33:57 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(char	*str)
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
	else
		return (false);
}

void	exe_builtin(char **args, t_env **ft_env, t_gc **gc)
{
	if (!ft_strcmp(args[0], "env"))
		cmd_env(args, ft_env);
	else if (!ft_strcmp(args[0], "export"))
		export(args, ft_env, gc);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(args, gc);
	else if (!ft_strcmp(args[0], "echo"))
		echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		cd(args, gc);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(args, ft_env);
}

static char	**dp_env(t_env **ft_env, t_gc **gc)
{
	char	**res;
	int		i;
	t_env	*head;
	int		len;

	i = 0;
	len = ft_envsize(*ft_env);
	head = *ft_env;
	res = ft_malloc((len + 1 )* sizeof(char *), gc);
	while (i < len || head)
	{
		res[i] = ft_strjoin(head->name, "=", gc);
		res[i] = ft_strjoin(res[i], head->value, gc);
		i++;
		head = head->next;
	}
	res[i] = NULL;
	return (res);
}

char	*check_cmd(char **args, t_env **ft_env, t_gc **gc)
{
	char	*path;
	char	**paths;
	char	*cmd;
	int		i;

	path = ft_strdup(ft_getenv("PATH", ft_env), gc);
	cmd = ft_strjoin("/", args[0], gc);
	paths = ft_vanilla_split(path, ':', 0, 0);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd, gc);
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
				return (path);
			else
			{
				ft_putstr_fd(args[0], 2);
				ft_putstr_fd(" : permission denied", 2);
				exit(126);
			}
		}
		i++;
	}
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(" : command not found", 2);
	exit(127);//free_paths
}


void	exe_cmd(char **args, t_env **ft_env, t_gc **gc)
{
	char	**env;
	pid_t	pid;
	char	*path;

	if (is_builtin(args[0]))
		exe_builtin(args, ft_env, gc);
	else
	{
		env = dp_env(ft_env, gc);
		if (args[0][0] == '/' || ft_strinstr(args[0], "./"))
			path = args[0];
		else
			path = check_cmd(args, ft_env, gc);
		pid = fork();
		if (pid == -1)
			perror("Fork");
		if (!pid)
		{
			if (execve(path, args, env) == -1)
				perror("Execve");
		}
		else if (pid)
			waitpid(pid, NULL, 0);
	}
}
