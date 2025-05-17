/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:02:36 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/17 11:41:12 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	void	redr_helper(t_leaf *tmp, t_container *c, int *p_fd, int flag)
{
	if (flag)
	{
		ft_dup2(tmp->token->out, 1, p_fd, c);
		close(tmp->token->out);
	}
	else
	{
		ft_dup2(tmp->token->in, 0, p_fd, c);
		close(tmp->token->out);
	}
}

void	child2_helper(t_leaf *tmp, t_container *c, int *p_fd, int *fds)
{
	if (tmp->token->out > 0)
		redr_helper(tmp, c, p_fd, 1);
	else if (tmp->token->out < 0)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	else
		ft_dup2(p_fd[1], 1, p_fd, c);
	if (tmp->token->in > 0)
		redr_helper(tmp, c, p_fd, 1);
	else if (tmp->token->out < 0)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	else
		ft_dup2(fds[0], 0, p_fd, c);
}

void	child3_helper(t_leaf *tmp, t_container *c, int *p_fd)
{
	if (tmp->token->out > 0)
		redr_helper(tmp, c, p_fd, 1);
	else if (tmp->token->out < 0)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	if (tmp->token->in > 0)
		redr_helper(tmp, c, p_fd, 0);
	else if (tmp->token->out < 0)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	else
		ft_dup2(p_fd[0], 0, p_fd, c);
}
