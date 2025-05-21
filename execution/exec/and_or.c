/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:13:58 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/21 12:48:02 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	child(t_leaf **root, char **args, t_container *c)
{
	char	**env;
	char	*path;
	t_leaf	*tmp;

	tmp = *root;
	redr_cmd(tmp, c);
	path = resolve_path(args, c->ft_env, c->garbage);
	env = dp_env(c->ft_env, c->garbage);
	if (execve(path, args, env) == -1)
		exevce_fail(path, c);
}

static void	exe(char **args, t_leaf **root, t_container *c)
{
	pid_t	pid;
	t_leaf	*tmp;

	tmp = *root;
	if (is_builtin(args[0]))
		c->status = exe_builtin(args, tmp, c);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("Fork");
		if (!pid)
			child(root, args, c);
		else if (pid)
		{
			close_redr(root);
			waitpid(pid, &c->status, 0);
			c->status = WEXITSTATUS(c->status);
		}
	}
}

static void	cmd(t_leaf **root, t_container *c)
{
	t_leaf	*node;
	char	**args;
	int		i;

	i = 0;
	node = *root;
	args = ft_args_split(node->token->token, c->garbage, 0, 0);
	while (args[i])
	{
		args[i] = expander(args[i], c);
		i++;
	}
	exe(args, root, c);
}

void	exe_and(t_leaf **root, t_container *c)
{
	t_leaf	*node;

	node = *root;
	if (node->right->type == AND)
		exe_and(&node->right, c);
	else if (node->right->type == PIPE)
		pipe_handle(&node->right, NULL, c, 1);
	else if (node->right->type == COMMAND)
		cmd(&node->right, c);
	if (node->left->type == PIPE && c->status == 0)
		pipe_handle(&node->left, NULL, c, 1);
	else if (node->left->type == COMMAND && c->status == 0)
		cmd(&node->left, c);
}

//andother or
void	exe_or(t_leaf **root, t_container *c)
{
	t_leaf	*node;

	node = *root;
	if (node->right->type == OR)
		exe_or(&node->right, c);
	else if (node->right->type == AND)
		exe_and(&node->right, c);
	else if (node->right->type == PIPE)
		pipe_handle(&node->right, NULL, c, 1);
	else if (node->right->type == COMMAND)
		cmd(&node->right, c);
	if (node->left->type == AND && c->status != 0)
		exe_and(&node->left, c);
	else if (node->left->type == PIPE && c->status != 0)
		pipe_handle(&node->left, NULL, c, 1);
	else if (node->left->type == COMMAND && c->status != 0)
		cmd(&node->left, c);
}
