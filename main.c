/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 11:13:02 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	g_signal = 0;

void	start(char *line, t_c *c)
{
	if (syntax_error(line))
	{
		if (tokenizer(c->root, c->garbage, line))
		{
			execc(c);
			close_heredoc(c->root, c);
		}
	}
}

static void	minishell_init(t_c *c, int ac, char **av, char **env)
{
	if (ac > 1)
	{
		(void)av;
		ft_putstr_fd("too many arguments\n", 2);
		exit(1);
	}
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		exit(1);
	signal(SIGINT, handler);
	c->status = 0;
	env_init(env, c->ft_env, c->garbage);
	env_check_path(c->ft_env, 0);
}

void	loop(t_container *container)
{
	while (true)
	{
		g_signal = SIGINT;
		container->pid = get_pid_str(container);
		container->line = readline("Minishell$>");
		if (!container->line)
			ft_exit(NULL, container->ft_env, container->garbage,
				set_status(0, 0));
		add_history(container->line);
		g_signal = 0;
		ft_add_gc(container->garbage, ft_new_gc_node(container->line));
		container->line = formating(container->line, container->garbage);
		if (!container->line[0])
			continue ;
		start(container->line, container);
		free_garbage(container->garbage);
	}
}

int	main(int ac, char **av, char **env)
{
	t_c		c;
	t_gc	*gc;
	t_leaf	*root;
	t_env	*ft_env;

	gc = NULL;
	root = NULL;
	ft_env = NULL;
	container.root = &root;
	container.ft_env = &ft_env;
	container.garbage = &gc;
	minishell_init(&container, ac, av, env);
	loop(&container);
	return (0);
}
