/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:56:50 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/28 15:36:47 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fork_fail(t_container *c)
{
	close_heredoc(c->root, c);
	free_garbage(c->garbage);
	ft_free_env(c->ft_env);
	exit(1);
}

// void	pipe_handle(t_leaf **root, int *fds, t_container *c, int flag)
// {
// // 	t_leaf	*node;
// // 	static int	d;

// // 	node = *root;
// // 	if (node->token->subshell > d)
// // 	{
// // 		d = node->token->subshell;
// // 		exe_subshell(c->root, c);
// // 	}
// // 	if (flag)
// // 		fds = ft_malloc((2 * sizeof(int)), c->garbage);
// // 	if (node->right->type == PIPE)
// // 		pipe_handle(&node->right, fds, c, 0);
// // 	else if (node->right->type == COMMAND)
// // 		child1(c, &node->right, fds);
// // 	ext_pipe(node, fds, c, flag);
// 	printf("here\n");
// }

// void	subshell_pipe(t_leaf **root, t_container *c, int *fds)
// {
// 	pid = fork();
// 	if (pid == -1)
// 		fork_fail(c);
// 	else if (!pid)
// 		pipe_handle(root, fds, c, flag);
// 	else
// 	{
// 		waitpid(pid, &c->status, 0);
// 		set_status(WIFEXITED(c->status), -1);
// 	}
// }


// void	exe_subshell(t_leaf **root, t_container *c)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		fork_fail(c);
// 	else if (!pid)
// 		subshell(root, c);
// 	else
// 	{
// 		waitpid(pid, &c->status, 0);
// 		set_status(WIFEXITED(c->status), -1);
// 	}
// }
