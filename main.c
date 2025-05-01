/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/01 10:59:54 by moel-oua         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_gc	*garbage;
	t_env	*ft_env;

	(void)ac;
	(void)av;
	garbage = NULL;
	ft_env = NULL;
	env_init(env, &ft_env, &garbage);
	load_history();
	while (true)
	{
		line = readline("Minishell: ");
		if (!line)
			exit(0);
		line = formating(line, &garbage);
		if (!line[0])
			continue ;
		add_history(line);
		save_history();
		if (syntax_error(line))
		{
			tokenizer(&garbage, line);
		}
		free(line);
	}
	return (0);
}
