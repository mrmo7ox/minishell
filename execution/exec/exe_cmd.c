/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:02:42 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/16 13:19:35 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**dp_env(t_env **ft_env, t_gc **gc)
{
	char	**res;
	int		i;
	t_env	*head;
	int		len;

	i = 0;
	len = ft_envsize(*ft_env);
	head = *ft_env;
	res = ft_malloc((len + 1) * sizeof(char *), gc);
	if (!res)
	{
		perror("malloc");
		exit (1);
	}
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
			ft_putstr_fd(path, 2);
			ft_putstr_fd(" : permission denied\n", 2);
			exit_exe(ft_env, gc, 126);
		}
	}
	else
	{
		if (!args[0][0])
			ft_putstr_fd("\'\'", 2);
		else
			ft_putstr_fd(args[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		exit_exe(ft_env, gc, 127);
	}
}

char	*resolve_path(char **args, t_env **ft_env, t_gc **gc)
{
	char	*path;

	if (ft_chrstr('/', args[0]) || !args[0][0])
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

void	child(char **args, t_container *c)
{
	char	**env;
	char	*path;
	t_leaf	*tmp;

	tmp = *(c->root);
	if (tmp->token->in > 0)
	{
		if (dup2(tmp->token->in, 0) == -1)
		{
			perror("dup2");
			exit_exe(c->ft_env, c->garbage, 1);
		}
	}
	if (tmp->token->out > 0)
	{
		if (dup2(tmp->token->out, 1) == -1)
		{
			perror("dup2");
			exit_exe(c->ft_env, c->garbage, 1);
		}
	}
	path = resolve_path(args, c->ft_env, c->garbage);
	env = dp_env(c->ft_env, c->garbage);
	if (execve(path, args, env) == -1)
		exevce_fail(path, c);
}

void	exe_cmd(char **args, t_container *c)
{
	pid_t	pid;
	t_leaf	*tmp;

	tmp = *(c->root);
	if (is_builtin(args[0]))
		c->status = exe_builtin(args, tmp, c);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("Fork");
		if (!pid)
			child(args, c);
		else if (pid)
		{
			waitpid(pid, &c->status, 0);
			c->status = WEXITSTATUS(c->status);
		}
	}
}
