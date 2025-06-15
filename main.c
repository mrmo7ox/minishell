/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/15 11:26:43 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int			g_signal;

void	start(char *line, t_c *c)
{
	if (syntax_error(line))
	{
		if (tokenizer(c->root, c, line))
		{
			execc(c);
			close_heredoc(c->root, c);
		}
	}
}

static void	minishell_init(t_c *c, int ac, char **av, char **env)
{
	g_signal = 0;
	if (ac > 1)
	{
		(void)av;
		ft_putstr_fd("too many arguments\n", 2);
		exit(1);
	}
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		exit(1);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	c->status = 0;
	env_init(env, c->ft_env);
	env_check_path(c->ft_env, 0);
}

void	loop(t_c *c)
{
	while (true)
	{
		g_signal = SIGINT;
		c->pid = get_pid_str(c);
		c->line = readline("Minishell$> ");
		if (!c->line)
			ft_exit(NULL, c->ft_env, c->garbage, set_status(0, 0));
		add_history(c->line);
		g_signal = 0;
		ft_add_gc(c->garbage, ft_new_gc_node(c->line));
		c->line = formating(c->line, c->garbage);
		if (!c->line[0])
			continue ;
		start(c->line, c);
		free_garbage(c->garbage);
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
	c.root = &root;
	c.ft_env = &ft_env;
	c.garbage = &gc;
	minishell_init(&c, ac, av, env);
	loop(&c);
	return (0);
}
