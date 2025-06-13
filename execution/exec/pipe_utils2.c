/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:58:48 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/31 17:41:49 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_err(char *str, t_c *c, int *fds)
{
	if (fds)
	{
		close(fds[0]);
		close(fds[1]);
	}
	ft_free_env(c->ft_env);
	free_garbage(c->garbage);
	perror(str);
	exit(1);
}

void	pid_wait(t_c *c, pid_t pid)
{
	int	tmp;

	tmp = 0;
	waitpid(pid, &c->status, 0);
	set_status(WEXITSTATUS(c->status), -1);
	while (wait(&tmp) != -1)
		continue ;
	handle_signal_pip(tmp, c->status);
}

static void	ext_exevce_fail(t_c *c)
{
	ft_free_env(c->ft_env);
	free_garbage(c->garbage);
}

void	exevce_fail(char *path, t_c *c)
{
	struct stat	statbuf;

	if (access(path, X_OK) != -1)
	{
		if (stat(path, &statbuf) == -1)
		{
			perror("stat");
			ext_exevce_fail(c);
			exit(1);
		}
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			ext_exevce_fail(c);
			exit(126);
		}
		else
		{
			ft_free_env(c->ft_env);
			ext_exevce_fail(c);
			exit(0);
		}
	}
	perror("execve");
}

void	close_redr(t_leaf **root)
{
	if ((*root)->token->in > 0)
	{
		close((*root)->token->in);
		(*root)->token->in = 0;
	}
	if ((*root)->token->out > 0)
	{
		close((*root)->token->out);
		(*root)->token->out = 0;
	}
}
