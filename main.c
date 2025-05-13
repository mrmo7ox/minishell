/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/13 15:29:53 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void start(char *line, t_container *container)
{
	add_history(line);
	save_history();
	if (syntax_error(line))
	{
		if (tokenizer(container->root, container->garbage, line))
		{
			execc(container);
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
	// if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	// 	exit(1);
	container->status = 0;
	env_init(env, container->ft_env, container->garbage);
	pwd_update(container->ft_env, 0);
	env_check_path(container->ft_env, 0);
}

int	main(int ac, char **av, char **env)
{
	t_container	container;
	t_gc		*gc;
	t_leaf		*root;
	t_env		*ft_env;

	gc = NULL;
	root = NULL;
	ft_env = NULL;
	container.root = &root;
	container.ft_env = &ft_env;
	container.garbage = &gc;
	minishell_init(&container, ac, av, env);
	load_history();
	while (true)
	{
		container.line = readline("Minishell$>");
		if (!container.line)
			ft_exit(NULL, container.ft_env, container.garbage,
				container.status);
		ft_add_gc(container.garbage, ft_new_gc_node(container.line));
		container.line = formating(container.line, container.garbage);
		if (!container.line[0])
			continue ;
		start(container.line, &container);
		free_garbage(container.garbage);
	}
	return (0);
}
