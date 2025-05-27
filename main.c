/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/27 14:21:06 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int			g_signal = 0;

void	start(char *line, t_container *container)
{
	add_history(line);
	save_history();
	if (syntax_error(line))
	{
		if (tokenizer(container->root, container->garbage, line))
		{
			execc(container);
			close_heredoc(container->root, container);
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
	signal(SIGINT, handler);
	container->status = 0;
	env_init(env, container->ft_env, container->garbage);
	env_check_path(container->ft_env, 0);
}

char	*prompt(t_container *c)
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
	container.pid = get_pid_str(&container);
	minishell_init(&container, ac, av, env);
	load_history();
	while (true)
	{
		g_signal = SIGINT;
		container.line = readline(prompt(&container));
		if (!container.line)
			ft_exit(NULL, container.ft_env, container.garbage,
				container.status);
		g_signal = 0;
		ft_add_gc(container.garbage, ft_new_gc_node(container.line));
		container.line = formating(container.line, container.garbage);
		if (!container.line[0])
			continue ;
		start(container.line, &container);
		free_garbage(container.garbage);
	}
	return (0);
}
