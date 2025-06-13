/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:40:11 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/31 14:48:15 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ext_child2(int *p_fd, t_leaf **root, t_c *c, int *fds)
{
	char	**args;
	t_leaf	*tmp;

	signal(SIGQUIT, SIG_DFL);
	tmp = *root;
	if (!tmp->token->token)
	{
		exec_redirec(tmp->token, c);
		close_fds(tmp, fds, p_fd);
		close_heredoc(c->root, c);
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 0);
	}
	args = ft_args_split(tmp->token->token, c->garbage);
	args = expander(args, c);
	child2_helper(tmp, c, p_fd, fds);
	close_fds(tmp, fds, p_fd);
	close_heredoc(c->root, c);
	if (!args)
		exit_exe(c->ft_env, c->garbage, 1);
	exe_pipe(args, c);
}

void	child2(t_c *c, t_leaf **root, int *fds)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		pipe_err("Fork", c, fds);
	pid = fork();
	if (pid == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		pipe_err("Fork", c, fds);
	}
	else if (!pid)
		ext_child2(p_fd, root, c, fds);
	else
	{
		close(fds[0]);
		close(fds[1]);
		fds[0] = p_fd[0];
		fds[1] = p_fd[1];
	}
}

static void	ext_child3(t_leaf **root, t_c *c, int *fds)
{
	char	**args;
	t_leaf	*tmp;

	signal(SIGQUIT, SIG_DFL);
	tmp = *root;
	if (!tmp->token->token)
	{
		exec_redirec(tmp->token, c);
		close_fds(tmp, fds, NULL);
		close_heredoc(c->root, c);
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 0);
	}
	args = ft_args_split(tmp->token->token, c->garbage);
	args = expander(args, c);
	child3_helper(tmp, c, fds);
	close_fds(tmp, fds, NULL);
	close_heredoc(c->root, c);
	if (!args)
		exit_exe(c->ft_env, c->garbage, 0);
	exe_pipe(args, c);
}

pid_t	child3(t_c *c, t_leaf **root, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		pipe_err("Fork", c, fds);
	else if (!pid)
		ext_child3(root, c, fds);
	else
	{
		close(fds[0]);
		close(fds[1]);
		return (pid);
	}
	return (pid);
}

void	cmd_no_args(t_leaf *tmp, t_c *c)
{
	exec_redirec(tmp->token, c);
	close_redr(&tmp);
	close_heredoc(c->root, c);
}
