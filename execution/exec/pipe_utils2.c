/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:58:48 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/13 10:00:55 by ihamani          ###   ########.fr       */
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
