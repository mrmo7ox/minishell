/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:58:48 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/13 11:14:08 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_err(char *str, t_container *c, int *fds)
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

void	pid_wait(t_container *c, pid_t pid)
{
	waitpid(pid, &c->status, 0);
	c->status = WEXITSTATUS(c->status);
	wait(NULL);
}

static void	ext_exevce_fail(t_container *c)
{
	ft_free_env(c->ft_env);
	free_garbage(c->garbage);
}

void	exevce_fail(char *path, t_container *c)
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
