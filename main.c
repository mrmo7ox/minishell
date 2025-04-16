/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/16 14:06:14 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	printf_garbage(t_gc *garbage)
 {
 	int i = 0;
 
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

int main(void)
{
	char	*line;
	t_gc	*garbage = NULL;
	t_node	*root = NULL;
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
			tokenizer(&garbage, line , &root);
		}
		printf_garbage(garbage);
		// if()
		// {	
		// 	// ft_add_gc(&garbage, ft_new_gc_node(line));
		// 	// tokenizer(&garbage, &tokens, line);
		// }
		free(line);
	}
}


// for testing 
// int main(int ac , char **dc)
// {
// 	char	*line;
// 	t_gc	*garbage;
// 	t_tk	*tokens;

	
// 	if(ac >= 2 )
	
// 	{
// 		int i = 1;
// 		line = dc[i];
// 		while(dc[i])
// 		{
// 			i++;
// 			line = ft_strjoin(line, dc[i]);
// 		}
// 		printf("[TEST] [%s]\n", line);
// 		ft_add_gc(&garbage, ft_new_gc_node(line));
// 		tokenizer(&garbage, &tokens, line);
// 	}
// }
