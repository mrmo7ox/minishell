/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:02:36 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/29 21:39:20 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redr_helper(t_leaf *tmp, t_c *c, int *p_fd, int flag)
{
	if (flag)
	{
		if (dup2(tmp->token->out, 1) == -1)
		{
			perror("dup2");
			close_fds(tmp, NULL, p_fd);
			exit_exe(c->ft_env, c->garbage, 1);
		}
		close(tmp->token->out);
	}
	else
	{
		if (dup2(tmp->token->in, 0) == -1)
		{
			perror("dup2");
			close_fds(tmp, NULL, p_fd);
			exit_exe(c->ft_env, c->garbage, 1);
		}
		close(tmp->token->in);
	}
}

void	child2_helper(t_leaf *tmp, t_c *c, int *p_fd, int *fds)
{
	child2_pipe(tmp, c, fds, p_fd);
	exec_redirec(tmp->token, c);
	if (tmp->token->out > 0)
		redr_helper(tmp, c, p_fd, 1);
	else if (tmp->token->out < 0)
	{
		close_fds(tmp, NULL, p_fd);
		close_heredoc(c->root, c);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	if (tmp->token->in > 0)
		redr_helper(tmp, c, p_fd, 0);
	else if (tmp->token->in < 0)
	{
		close_fds(tmp, NULL, p_fd);
		close_heredoc(c->root, c);
		exit_exe(c->ft_env, c->garbage, 1);
	}
}

void	child3_helper(t_leaf *tmp, t_c *c, int *p_fd)
{
	if (dup2(p_fd[0], 0) == -1)
	{
		close_fds(tmp, NULL, p_fd);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	exec_redirec(tmp->token, c);
	if (tmp->token->out > 0)
		redr_helper(tmp, c, p_fd, 1);
	else if (tmp->token->out < 0)
	{
		close_fds(tmp, NULL, p_fd);
		close_heredoc(c->root, c);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	if (tmp->token->in > 0)
		redr_helper(tmp, c, p_fd, 0);
	else if (tmp->token->in < 0)
	{
		close_fds(tmp, NULL, p_fd);
		close_heredoc(c->root, c);
		exit_exe(c->ft_env, c->garbage, 1);
	}
}

void	child1_helper(t_leaf *tmp, t_c *c, int *p_fd)
{
	if (dup2(p_fd[1], 1) == -1)
	{
		perror("dup2");
		close_fds(tmp, NULL, p_fd);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	exec_redirec(tmp->token, c);
	if (tmp->token->out > 0)
		redr_helper(tmp, c, p_fd, 1);
	else if (tmp->token->out < 0)
	{
		close_fds(tmp, NULL, p_fd);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	if (tmp->token->in > 0)
		redr_helper(tmp, c, p_fd, 0);
	else if (tmp->token->in < 0)
	{
		close_fds(tmp, NULL, p_fd);
		exit_exe(c->ft_env, c->garbage, 1);
	}
}
