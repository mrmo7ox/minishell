/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:40:11 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/16 16:35:55 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ext_child2(int *p_fd, t_leaf **root, t_container *c, int *fds)
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
	if (tmp->token->out > 0)
		ft_dup2(tmp->token->out, 1, p_fd, c);
	else if (tmp->token->out < 0)
		exit_exe(c->ft_env, c->garbage, 1);
	else
		ft_dup2(p_fd[1], 1, p_fd, c);
	if (tmp->token->in > 0)
		ft_dup2(tmp->token->in, 0, p_fd, c);
	else if (tmp->token->out < 0)
		exit_exe(c->ft_env, c->garbage, 1);
	else
		ft_dup2(fds[0], 0, p_fd, c);
	close(fds[0]);
	close(fds[1]);
	close(p_fd[1]);
	close(p_fd[0]);
	exe_pipe(tmp, args, c);
}

void	child2(t_container *c, t_leaf **root, int *fds)
{
	int		p_fd[2];
	int		status;
	pid_t	pid;

	if (!(*root)->token->token)
		return ;
	status = 0;
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

static void	ext_child3(t_leaf **root, t_container *c, int *fds)
{
	char	**args;
	int		i;
	t_leaf	*tmp;

	i = 0;
	tmp = *root;
	args = ft_args_split(tmp->token->token, c->garbage, 0, 0);
	while (args[i])
	{
		args[i] = expander(args[i], c);
		i++;
	}
	if (tmp->token->out > 0)
		ft_dup2(tmp->token->out, 1, NULL, c);
	else if (tmp->token->out < 0)
		exit_exe(c->ft_env, c->garbage, 1);
	if (tmp->token->in > 0)
		ft_dup2(tmp->token->in, 0, NULL, c);
	else if (tmp->token->out < 0)
		exit_exe(c->ft_env, c->garbage, 1);
	else
		ft_dup2(fds[0], 0, NULL, c);
	close(fds[0]);
	close(fds[1]);
	exe_pipe(tmp, args, c);
}

pid_t	child3(t_container *c, t_leaf **root, int *fds)
{
	int		i;
	pid_t	pid;

	if (!(*root)->token->token)
		return (0);
	i = 0;
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

void	ft_dup2(int fd1, int fd2, int *p_fd, t_container *c)
{
	if (dup2(fd1, fd2) == -1)
	{
		if (p_fd)
		{
			close(p_fd[0]);
			close(p_fd[1]);
		}
		ft_free_env(c->ft_env);
		free_garbage(c->garbage);
		perror("dup2");
		exit(1);
	}
}
