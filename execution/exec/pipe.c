/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:58:12 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/12 10:24:25 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exe_pipe(t_leaf *tmp, char **args, t_container *c)
{
	char	**env;
	char	*path;

	if (is_builtin(args[0]))
		exit(exe_builtin(args, tmp, c));
	else
	{
		path = resolve_path(args, c->ft_env, c->garbage);
		env = dp_env(c->ft_env, c->garbage);
		if (execve(path, args, env) == -1)
		{
			if (access(path, X_OK) != -1)
				exit(0); // handle dir
			perror("execve");
		}
	}
}

static void	ext_child1(int *p_fd, t_leaf **root, t_container *c, int *fds)
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
	if (tmp->token->out)
		ft_dup2(tmp->token->out, 1, p_fd, c);
	else
		ft_dup2(p_fd[1], 1, p_fd, c);
	if (tmp->token->in)
		ft_dup2(tmp->token->in, 0, p_fd, c);
	close(p_fd[1]);
	close(p_fd[0]);
	exe_pipe(tmp, args, c);
}

static pid_t	child1(t_container *c, t_leaf **root, int *fds)
{
	int		i;
	int		p_fd[2];
	pid_t	pid;

	i = 0;
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		fork_err(c, p_fd);
	}
	else if (!pid)
		ext_child1(p_fd, root, c, fds);
	else
	{
		fds[0] = p_fd[0];
		fds[1] = p_fd[1];
	}
	return (pid);
}
// void	print_node(t_leaf *node, char *l)
// {
// 	if (!node || !node->token)
// 		return ;
// 	printf("[%s]", l);
// 	if (node->type == AND)
// 		printf("Operator: &&\n");
// 	else if (node->type == OR)
// 		printf("Operator: ||\n");
// 	else if (node->type == PIPE)
// 		printf("Operator: |\n");
// 	else
// 		printf("Command: %s\n", node->token->token);
// }

// void print_ast(t_leaf *root, char *l, int depth)
// {
// 	if (!root)
// 		return ;

// 	for (int i = 0; i < depth; i++)
// 		printf("  ");

// 	print_node(root, l);

// 	print_ast(root->left, "left", depth + 1);
// 	print_ast(root->right, "right", depth + 1);
// print_ast(node, "O", 0);
// }
void	pipe_handle(t_leaf **root, t_pipe *pip, t_container *c, int flag)
{
	t_leaf	*node;

	node = *root;
	if (flag)
		init_pip(pip, c->garbage);
	if (node->right->type == PIPE)
		pipe_handle(&node->right, pip, c, 0);
	else if (node->right->type == COMMAND)
	{
		exec_redirec(node->right->token, c);
		add_towait(pip->lst, ft_new_towait(child1(c, &node->right,
					pip->fds), c->garbage));
	}
	if (node->left->type == COMMAND)
	{
		if (!flag)
		{
			exec_redirec(node->left->token, c);
			add_towait(pip->lst, ft_new_towait(child2(c, &node->left,
						pip->fds), c->garbage));
		}
		else
		{
			exec_redirec(node->left->token, c);
			add_towait(pip->lst, ft_new_towait(child3(c, &node->left,
						pip->fds), c->garbage));
		}
	}
}
