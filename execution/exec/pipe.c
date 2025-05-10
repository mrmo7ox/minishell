/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:58:12 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/10 14:56:08 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	dup_protect(t_pipe pip)
{
	close(pip->fd);
	close(pip->p_fd[1]);
	close(pip->p_fd[0]);
	perror("dup2");
	exit(1);
}

static void	execve_pro(t_pipe *pip, t_env **ft_env, t_gc **gc)
{
	free_garbage(gc);
	ft_free_env(env);
	if (access(path, X_OK) != -1)
		exit(0);
	perror("execv");
	exit(-1);
}

static void	child(char **args, t_pipe *pip, t_env **ft_env, t_gc **gc)
{
	char	**env;
	char	*path;

	if (pip->fd != -1)
	{
		if (dup2(pip->fd, 1) == -1)
			dup_protect(pip);
		close(pip->fd);
	}
	if (dup2(pip->p_fd[1], 0) == -1)
		dup_protect(pip);
	pip->fd = pipe->p_fd[0];
	if (is_builtin(args[0]))
		pip->status = exe_builtin(args, ft_env, gc);
	else
	{
		path = resolve_path(args, ft_env, gc);
		env = dp_env(ft_env, gc);
		if (execve(path, args, env) == -1)
			execve(pip, ft_env, gc);
	}
}

static void	exe_pipe(char **args, t_pipe *pip, t_env **ft_env, t_gc **gc)
{
	if (pipe(pip->p_fd) == -1)
	{
		perror("Pipe");
		pip->status = -1;
		return ;
	}
	pip->pid = fork();
	if (pip->pid == -1)
	{
		perror("Fork");
		pip->status = -1;
		return ;
	}
	if (!pip->pid)
		child(args, pip, ft_env, gc);
	else
	{
		close(pip->p_fd[0]);
		close(pip->p_fd[1]);
		waitpid(pip->pid, &pip->status, 0);
	}
}

t_leaf	*pipe_handle(t_leaf **root, t_pipe *pip, t_container *c)
{
	t_leaf	*node;

	node = *root;
	if (!pip)
		new_pip(-1, 0, gc);
	if (node->right)
		pip->fd = exe_pipe(node->token->token, pip, ft_env, gc);
	if (pip-> status == 0 && node->left->type == PIPE)
		pipe_handle(node->left, pip, ft_env, gc);
	else if (pip-> status == 0 && node->left->type == COMMAND)
		pip->fd = exe_pipe(node->token->token, pip, ft_env, gc);
	else
		return (node->left);
}
