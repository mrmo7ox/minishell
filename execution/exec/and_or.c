/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:13:58 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/27 13:44:53 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	child(t_leaf **root, char **args, t_container *c)
{
	char	**env;
	char	*path;
	t_leaf	*tmp;

	tmp = *root;
	exec_redirec(tmp->token, c);
	redr_cmd(tmp, c);
	close_redr(&tmp);
	close_heredoc(c->root, c);
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
	{
		c->status = exe_builtin(args, tmp, c);
		set_status(c->status, -1);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			perror("Fork");
		if (!pid)
			child(root, args, c);
		else if (pid)
		{
			waitpid(pid, &c->status, 0);
			set_status(WEXITSTATUS(c->status), -1);
			if (WIFSIGNALED(c->status))
			{
				set_status(130, -1);
				write(1, "\n", 1);
			}
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
	args = expander(args, c);
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
	if (node->left->type == PIPE && set_status(c->status, 0) == 0)
		pipe_handle(&node->left, NULL, c, 1);
	else if (node->left->type == COMMAND && set_status(c->status, 0) == 0)
		cmd(&node->left, c);
}

// andother or
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
	if (node->left->type == AND && set_status(c->status, 0) != 0
		&& set_status(0, 0) != 130)
		exe_and(&node->left, c);
	else if (node->left->type == PIPE && set_status(c->status, 0) != 0
		&& set_status(0, 0) != 130)
		pipe_handle(&node->left, NULL, c, 1);
	else if (node->left->type == COMMAND && set_status(c->status, 0) != 0
		&& set_status(0, 0) != 130)
		cmd(&node->left, c);
}
