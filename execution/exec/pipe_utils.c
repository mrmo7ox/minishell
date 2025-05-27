/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:40:11 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/27 10:58:44 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ext_child2(int *p_fd, t_leaf **root, t_container *c, int *fds)
{
	char	**args;
	t_leaf	*tmp;

	tmp = *root;
	args = ft_args_split(tmp->token->token, c->garbage, 0, 0);
	args = expander(args, c);
	exec_redirec(tmp->token, c);
	child2_helper(tmp, c, p_fd, fds);
	close_fds(tmp, fds, p_fd);
	close_heredoc(c->root, c);
	exe_pipe(tmp, args, c);
}

void	child2(t_container *c, t_leaf **root, int *fds)
{
	int		p_fd[2];
	pid_t	pid;

	if (!(*root)->token->token)
		return ;
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
	args = expander(args, c);
	exec_redirec(tmp->token, c);
	child3_helper(tmp, c, fds);
	close_fds(tmp, fds, NULL);
	close_heredoc(c->root, c);
	exe_pipe(tmp, args, c);
}

pid_t	child3(t_container *c, t_leaf **root, int *fds)
{
	pid_t	pid;

	if (!(*root)->token->token)
		return (0);
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

void	ft_dup2(int fd1, int fd2, t_container *c)
{
	if (dup2(fd1, fd2) == -1)
	{
		ft_free_env(c->ft_env);
		free_garbage(c->garbage);
		perror("dup2");
		exit(1);
	}
}
