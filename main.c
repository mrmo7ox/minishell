/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:08 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/14 16:58:07 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int main(void)
{
	char	*line;
	t_gc	*garbage;
	t_tk	*tokens;

	while(true)
	{
		line = readline("Minishell: ");
		ft_add_gc(&garbage, ft_new_gc_node(line));
		tokenizer(&garbage, &tokens, line);
		free(line);
	}
}
