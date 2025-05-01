/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/01 11:38:48 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	printf_garbage(t_gc *garbage)
{
	int	i;

	i = 0;
	if (!garbage)
		printf("there's no garbage to clean! expet the dev\n");
	while (garbage)
	{
		i++;
		garbage = garbage->next;
	}
	if (i)
		printf("there's %d addr in the garbage!\n", i);
}

void	start(char *line, t_leaf **root, t_gc **garbage)
{
	add_history(line);
	save_history();
	if (syntax_error(line))
	{
		if (tokenizer(root, garbage, line))
			linker(root, expander);
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
	env_init(env, &container.ft_env, &container.garbage);
	load_history();
	while (true)
	{
		container.line = readline("Minishell: ");
		if (!container.line)
			exit(0);
		container.line = formating(container.line, &container.garbage);
		if (!container.line[0])
			continue ;
		start(container.line, &(container.root), &(container.garbage));
		free(container.line);
	}
	return (0);
}
