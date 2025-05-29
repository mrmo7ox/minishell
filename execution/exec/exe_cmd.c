/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:02:42 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/28 15:42:23 by ihamani          ###   ########.fr       */
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
		if (errno == 20)
		{
			perror(args[0]);
			exit_exe(ft_env, gc, 126);
		}
		else
		{
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(" : command not found\n", 2);
			exit_exe(ft_env, gc, 127);
		}
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

static void	child(char **args, t_container *c)
{
	char	**env;
	char	*path;
	t_leaf	*tmp;

	if (!args[0])
	{
		ft_putstr_fd("\'\'", 2);
		ft_putstr_fd(" : Command not found\n", 2);
		close_heredoc(c->root, c);
		exit_exe(c->ft_env, c->garbage, 127);
	}
	tmp = *(c->root);
	redr_cmd(tmp, c);
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
	if (!args)
	{
		exec_redirec(tmp->token, c);
		close_redr(&tmp);
		close_heredoc(c->root, c);
		set_status(0, -1);
		return ;
	}
	exec_redirec(tmp->token, c);
	if (is_builtin(args[0]))
		set_status(exe_builtin(args, tmp, c), -1);
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
			set_status(WEXITSTATUS(c->status), -1);
			if (WIFSIGNALED(c->status))
				write(1, "\n", 1);
		}
	}
	close_redr(&tmp);
}
