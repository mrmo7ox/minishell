/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/14 11:03:08 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int main(void)
{
	char	*line;
	t_gc	*garbage = NULL;
	t_tk	*tokens = NULL;
	t_node	*root = NULL;
	
	while (true)
	{
		line = readline("Minishell: ");
		line = formating(line);
		if (!ft_strlen(line))
			continue;
		add_history(line);
		if (syntax_error(line))
		{
			tokenizer(&garbage, &tokens, line , &root);
		}
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
