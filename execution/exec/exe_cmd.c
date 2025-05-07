/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:02:42 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/07 11:41:41 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**dp_env(t_env **ft_env, t_gc **gc)
{
	char	**res;
	int		i;
	t_env	*head;
	int		len;

	i = 0;
	len = ft_envsize(*ft_env);
	head = *ft_env;
	res = ft_malloc((len + 1) * sizeof(char *), gc);
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

void	check_path(char **args, char *path, t_env **ft_env, t_gc **gc)
{
	int	i;

	i = 0;
	if (path && !access(path, F_OK))
	{
		if (access(path, X_OK))
		{
			while (args[i])
				free(args[i++]);
			free(args);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(" : permission denied\n", 2);
			exit_exe(ft_env, gc, 126);
		}
	}
	else
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		while (args[i])
			free(args[i++]);
		free(args);
		exit_exe(ft_env, gc, 127);
	}
}

char	*resolve_path(char **args, t_env **ft_env, t_gc **gc)
{
	char	*path;

	if (ft_chrstr('/', args[0]))
	{
		path = ft_strdup(args[0], gc);
		check_path(args, path, ft_env, gc);
	}
	else
	{
		path = get_path(args, ft_env, gc);
		check_path(args, path, ft_env, gc);
	}
	return (path);
}

void	child(char **args, t_env **ft_env, t_gc **gc)
{
	char	**env;
	char	*path;

	path = resolve_path(args, ft_env, gc);
	env = dp_env(ft_env, gc);
	if (execve(path, args, env) == -1)
	{
		if (access(path, X_OK) != -1)
			exit(0);
		perror("execve");
	}
}

int	exe_cmd(char **args, t_tk *token, t_env **ft_env, t_gc **gc)
{
	pid_t	pid;
	int		status;

	(void)token;
	status = 0;
	if (is_builtin(args[0]))
		return (exe_builtin(args, ft_env, gc));
	else
	{
		pid = fork();
		if (pid == -1)
			perror("Fork");
		if (!pid)
			child(args, ft_env, gc);
		else if (pid)
			waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}
