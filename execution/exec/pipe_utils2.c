/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:58:48 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/11 12:55:18 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fork_err(t_container *c, int *fds)
{
	if (fds)
	{
		close(fds[0]);
		close(fds[1]);
	}
	ft_free_env(c->ft_env);
	free_garbage(c->garbage);
	perror("dup2");
	exit(1);
}
