/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:11 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/17 10:00:10 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	exe_cmd_hundler(t_leaf *node, t_container *c)
{
	char	**args;
	int		i;

	i = 0;
	args = NULL;
	if (node->token->token)
	{
		args = ft_args_split(node->token->token, c->garbage, 0, 0);
		while (args[i])
		{
			args[i] = expander(args[i], c);
			i++;
		}
		exe_cmd(args, c);
	}
	else
		return (false);
	return (true);
}

void	run_redirec(t_leaf **root,  t_container *c)
{
	 t_leaf *tmp;

    if (!root || !*root)
        return;
    tmp = *root;
	if (tmp->right)
		run_redirec(&tmp->right, c);
    if (tmp->left)
        run_redirec(&tmp->left, c);
    if (tmp->type == COMMAND)
        exec_redirec(tmp->token, c);
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

// }

int	execc(t_container *c)
{
	t_leaf	*node;
	t_leaf	**root;

	root = c->root;
	if (!(*root))
		return (1);
	node = *root;
	// if (node->token->subshell > 0 == COMMAND)
	// 	return (exe_subshell(node, ft_env, garbage));
	// print_ast(node, "O", 0);
	run_redirec(root, c);
	if (node->type == OR)
		exe_or(root, c);
	else if (node->type == AND)
		exe_and(root, c);
	else if (node->type == PIPE)
		pipe_handle(root, NULL, c, 1);
	else if (node->type == COMMAND)
		return (exe_cmd_hundler(node, c));
	return (1);
}
