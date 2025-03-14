/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/14 15:02:39 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	tokenizer(t_gc **garbage, t_tk **tokens, char *line)
{
	char	**splited;
	int		i;

	if (!line)
		return (false);
	splited = ft_split(line, ' ', 0, 0);
	if (!splited)
		return (false);
	*add_split_gc(garbage , splited);
	while (*splited)
	{
		if (*splited == '<' || *split)
			i = 0;
		if (i == 0)
			ft_add_tk (tokens, ft_new_tk_node (*splited, "cmd"));
		else 
		i++;
		*splited;
	}
	return (true);
}
