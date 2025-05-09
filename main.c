/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/09 15:10:33 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	start(char *line, t_leaf **root, t_gc **garbage, t_env **ft_env)
{
	add_history(line);
	save_history();
	if (syntax_error(line))
	{
		if (tokenizer(root, garbage, line))
		{
			execc(root, ft_env, garbage);
		}
	}
}

static void	minishell_init(t_container *container, int ac, char **av,
				char **env)
{
	if (ac > 1)
	{
		(void)av;
		ft_putstr_fd("too many arguments\n", 2);
		exit(1);
	}
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		exit(1);
	container->line = NULL;
	container->garbage = NULL;
	container->ft_env = NULL;
	container->root = NULL;
	container->ft_env = NULL;
	env_init(env, &container->ft_env, &(container->garbage));
}

int	main(int ac, char **av, char **env)
{
	t_container	container;

	minishell_init(&container, ac, av, env);
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
