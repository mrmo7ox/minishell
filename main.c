/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/16 16:10:49 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"


// int main(void)
// {
// 	char	*line;
// 	t_gc	*garbage;
// 	t_tk	*tokens;

// 	while(true)
// 	{
// 		line = readline("Minishell: ");
// 		add_history(line);
// 		syntax_error(line);
// 		(void)tokens;
// 		(void)garbage;
// 		// if()
// 		// {	
// 		// 	// ft_add_gc(&garbage, ft_new_gc_node(line));
// 		// 	// tokenizer(&garbage, &tokens, line);
// 		// }
// 		free(line);
// 	}
// }

// for testing 
int main(int ac , char **dc)
{
	char	*line;
	t_gc	*garbage;
	t_tk	*tokens;

	
	if(ac >= 2 )
	
	{
		int i = 1;
		line = dc[i];
		while(dc[i])
		{
			i++;
			line = ft_strjoin(line, dc[i]);
		}
		printf("[TEST] [%s]\n", line);
		ft_add_gc(&garbage, ft_new_gc_node(line));
		tokenizer(&garbage, &tokens, line);
	}
}
