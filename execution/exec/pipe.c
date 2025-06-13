/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:58:12 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/31 21:04:54 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exe_pipe(char **args, t_c *c)
{
	char	**env;
	char	*path;

	if (!args[0][0])
	{
		ft_putstr_fd("\'\'", 2);
		ft_putstr_fd(" : command not found\n", 2);
		exit_exe(c->ft_env, c->garbage, 127);
	}
	if (is_builtin(args[0]))
		exit_exe(c->ft_env, c->garbage, exe_builtin_pipe(args, c));
	else
	{
		path = resolve_path(args, c->ft_env, c->garbage);
		env = dp_env(c->ft_env, c->garbage);
		if (execve(path, args, env) == -1)
			exevce_fail(path, c);
	}
}

static void	ext_child1(int *p_fd, t_leaf **root, t_c *c)
{
	char	**args;
	t_leaf	*tmp;

	signal(SIGQUIT, SIG_DFL);
	tmp = *root;
	if (!tmp->token->token)
	{
		exec_redirec(tmp->token, c);
		close_fds(tmp, NULL, p_fd);
		close_heredoc(c->root, c);
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 0);
	}
	args = ft_args_split(tmp->token->token, c->garbage);
	args = expander(args, c);
	child1_helper(tmp, c, p_fd);
	close_fds(tmp, NULL, p_fd);
	close_heredoc(c->root, c);
	if (!args)
		exit_exe(c->ft_env, c->garbage, 0);
	exe_pipe(args, c);
}

static void	child1(t_c *c, t_leaf **root, int *fds)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		pipe_err("Fork", c, NULL);
	pid = fork();
	if (pid == -1)
		pipe_err("Fork", c, p_fd);
	else if (!pid)
		ext_child1(p_fd, root, c);
	else
	{
		fds[0] = p_fd[0];
		fds[1] = p_fd[1];
	}
}

static void	ext_pipe(t_leaf *node, int *fds, t_c *c, int flag)
{
	pid_t	last;

	last = 0;
	if (node->left->type == COMMAND)
	{
		if (!flag)
			child2(c, &node->left, fds);
		else
			last = child3(c, &node->left, fds);
	}
	if (flag)
		pid_wait(c, last);
}

void	pipe_handle(t_leaf **root, int *fds, t_c *c, int flag)
{
	t_leaf	*node;

	node = *root;
	if (flag)
		fds = ft_malloc((2 * sizeof(int)), c->garbage);
	if (node->right->type == PIPE)
		pipe_handle(&node->right, fds, c, 0);
	else if (node->right->type == COMMAND)
		child1(c, &node->right, fds);
	ext_pipe(node, fds, c, flag);
}
