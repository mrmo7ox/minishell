/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:02:36 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/21 11:08:22 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	void	redr_helper(t_leaf *tmp, t_container *c, int *p_fd, int flag)
{
	if (flag)
	{
		ft_dup2(tmp->token->out, 1, c);
		close(tmp->token->out);
	}
	else
	{
		ft_dup2(tmp->token->in, 0, c);
		close(tmp->token->in);
	}
}

void	child2_helper(t_leaf *tmp, t_container *c, int *p_fd, int *fds)
{
	if (tmp->token->out > 0)
		redr_helper(tmp, c, p_fd, 1);
	else if (tmp->token->out < 0)
	{
		close_fds();
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	else
		ft_dup2(p_fd[1], 1, c);
	if (tmp->token->in > 0)
		redr_helper(tmp, c, p_fd, 0);
	else if (tmp->token->in < 0)
	{
		close_fds();
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	else
		ft_dup2(fds[0], 0, c);
}

void	child3_helper(t_leaf *tmp, t_container *c, int *p_fd)
{
	if (tmp->token->out > 0)
		redr_helper(tmp, c, p_fd, 1);
	else if (tmp->token->out < 0)
	{
		close_fds();
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	if (tmp->token->in > 0)
		redr_helper(tmp, c, p_fd, 0);
	else if (tmp->token->in < 0)
	{
		close_fds();
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	else
		ft_dup2(p_fd[0], 0, c);
}

void	close_fds(void)
{
	int	i;

	i = 3;
	while (i < 1024)
		close(i++);
}

void	child1_helper(t_leaf *tmp, t_container *c, int *p_fd)
{
	if (tmp->token->out > 0)
		redr_helper(tmp, c, p_fd, 1);
	else if (tmp->token->out < 0)
	{
		close_fds();
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
	else
		ft_dup2(p_fd[1], 1, c);
	if (tmp->token->in > 0)
		redr_helper(tmp, c, p_fd, 0);
	else if (tmp->token->in < 0)
	{
		close_fds();
		close_redr(&tmp);
		exit_exe(c->ft_env, c->garbage, 1);
	}
}
