/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:58:12 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/16 16:35:02 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exe_pipe(t_leaf *tmp, char **args, t_container *c)
{
	char		**env;
	char		*path;

	if (is_builtin(args[0]))
		exit(exe_builtin(args, tmp, c));
	else
	{
		path = resolve_path(args, c->ft_env, c->garbage);
		env = dp_env(c->ft_env, c->garbage);
		if (execve(path, args, env) == -1)
			exevce_fail(path, c);
	}
}

static void	ext_child1(int *p_fd, t_leaf **root, t_container *c, int *fds)
{
	char	**args;
	t_leaf	*tmp;
	int		i;

	i = 0;
	tmp = *root;
	args = ft_args_split(tmp->token->token, c->garbage, 0, 0);
	while (args[i])
	{
		args[i] = expander(args[i], c);
		i++;
	}
	close(p_fd[0]);
	if (tmp->token->out > 0)
		ft_dup2(tmp->token->out, 1, p_fd, c);
	else if (tmp->token->out < 0)
		exit_exe(c->ft_env, c->garbage, 1);
	else
		ft_dup2(p_fd[1], 1, p_fd, c);
	if (tmp->token->in > 0)
		ft_dup2(tmp->token->in, 0, p_fd, c);
	else if (tmp->token->in < 0)
		exit_exe(c->ft_env, c->garbage, 1);
	close(p_fd[1]);
	exe_pipe(tmp, args, c);
}

static void	child1(t_container *c, t_leaf **root, int *fds)
{
	int		i;
	int		p_fd[2];
	pid_t	pid;

	i = 0;
	if (!(*root)->token->token)
		return ;
	if (pipe(p_fd) == -1)
		pipe_err("Fork", c, NULL);
	pid = fork();
	if (pid == -1)
		pipe_err("Fork", c, p_fd);
	else if (!pid)
		ext_child1(p_fd, root, c, fds);
	else
	{
		fds[0] = p_fd[0];
		fds[1] = p_fd[1];
	}
}

static	void	ext_pipe(t_leaf *node, int *fds, t_container *c, int flag)
{
	pid_t	last;

	last = 0;
	if (node->left->type == COMMAND)
	{
		if (!flag)
		{
			exec_redirec(node->left->token, c);
			child2(c, &node->left, fds);
		}
		else
		{
			exec_redirec(node->left->token, c);
			last = child3(c, &node->left, fds);
		}
	}
	if (flag)
		pid_wait(c, last);
}

void	pipe_handle(t_leaf **root, int *fds, t_container *c, int flag)
{
	t_leaf	*node;

	node = *root;
	if (flag)
		fds = ft_malloc((2 * sizeof(int)), c->garbage);
	if (node->right->type == PIPE)
		pipe_handle(&node->right, fds, c, 0);
	else if (node->right->type == COMMAND)
	{
		exec_redirec(node->right->token, c);
		child1(c, &node->right, fds);
	}
	ext_pipe(node, fds, c, flag);
}
