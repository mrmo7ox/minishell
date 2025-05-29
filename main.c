/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/29 21:39:38 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int			g_signal = 0;

void	start(char *line, t_c *c)
{
	add_history(line);
	save_history();
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

char	*prompt(t_c *c)
{
	char	*username;
	char	*pwd;
	char	*pro;

	username = ft_getenv("USER", c->ft_env);
	if (!username || !username[0])
		username = ft_strdup("Minishell", c->garbage);
	pwd = ft_getenv("PWD", c->ft_env);
	if (!pwd || !pwd[0])
	{
		pwd = getcwd(NULL, 0);
		ft_add_gc(c->garbage, ft_new_gc_node(pwd));
	}
	pro = ft_strjoin("\033[0;32m", username, c->garbage);
	pro = ft_strjoin(pro, "\033[0m:", c->garbage);
	pro = ft_strjoin(pro, pwd, c->garbage);
	pro = ft_strjoin(pro, "$ ", c->garbage);
	return (pro);
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
	load_history();
	while (true)
	{
		g_signal = SIGINT;
		c.pid = get_pid_str(&c);
		c.line = readline(prompt(&c));
		if (!c.line)
			ft_exit(NULL, c.ft_env, c.garbage, c.status);
		g_signal = 0;
		ft_add_gc(c.garbage, ft_new_gc_node(c.line));
		c.line = formating(c.line, c.garbage);
		if (!c.line[0])
			continue ;
		start(c.line, &c);
		free_garbage(c.garbage);
	}
	return (0);
}
