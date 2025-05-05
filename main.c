/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/05 19:03:31 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	start(char *line, t_leaf **root, t_gc **garbage, t_env **ft_env)
{
	char	**args;
	int		status;

	add_history(line);
	save_history();
	if (syntax_error(line))
	{
		if (tokenizer(root, garbage, line))
		{
			linker(root, expander, garbage, ft_env);
			remove_qoutes_tree(root, garbage);
			if (!(*root)->left && !(*root)->right)
			{
				args = ft_vanilla_split((*root)->token->token, ' ', 0, 0);
				status = exe_cmd(args, ft_env, garbage);
				printf("%d\n", status);
			}
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_container	container;

	(void)ac;
	(void)av;
	container.line = NULL;
	container.garbage = NULL;
	container.ft_env = NULL;
	container.root = NULL;
	container.ft_env = NULL;
	env_init(env, &container.ft_env);
	load_history();
	while (true)
	{
		container.line = readline("Minishell: ");
		if (!container.line)
			exit(0);
		container.line = formating(container.line, &container.garbage);
		if (!container.line[0])
			continue ;
		start(container.line, &(container.root), &(container.garbage),
			&container.ft_env);
		free_garbage(&container.garbage);
	}
	return (0);
}
