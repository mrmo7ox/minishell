/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:58:48 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/12 10:27:26 by ihamani          ###   ########.fr       */
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

t_towait	*ft_new_towait(pid_t pid, t_gc **gc)
{
	t_towait	*new;

	new = ft_malloc((1 * sizeof(t_towait)), gc);
	if (!new)
		return (NULL);
	new->pid = pid;
	return (new);
}

void	add_towait(t_towait **head, t_towait *new)
{
	t_towait	*last;

	if (!head || !new)
		return ;
	last = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

void	pid_wait(t_towait **lst, t_container *c)
{
	t_towait	*head;

	if (!lst || !*lst)
   		return ;
	head = *lst;
	while (head->next)
	{
		if (!head->pid)
		{
			head = head->next;
			continue ;
		}
		waitpid(head->pid, NULL, 0);
		head = head->next;
	}
	waitpid(head->pid, &c->status, 0);
	c->status = WEXITSTATUS(c->status);
}

void	init_pip(t_pipe *pip, t_gc **gc)
{
	pip->fds = ft_malloc((2 * sizeof(int)), gc);
	pip->lst = NULL;
}

