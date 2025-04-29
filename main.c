/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/29 10:14:52 by moel-oua         ###   ########.fr       */
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

int	main(void)
{
	char	*line;
	t_gc	*garbage;

	garbage = NULL;
	load_history();
	while (true)
	{
		line = readline("Minishell: ");
		line = formating(line, &garbage);
		if (!line)
			exit(0);
		add_history(line);
		save_history();
		if (syntax_error(line))
		{
			tokenizer(&garbage, line);
		}
		printf_garbage(garbage);
		free(line);
	}
	return (0);
}
