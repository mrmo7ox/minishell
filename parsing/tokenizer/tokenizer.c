/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/11 16:05:40 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	tokenizer(t_gc **garbage, t_tk **tokens, char *line)
{
	char	**splited;
	int		i;

	(void)garbage;
	(void)tokens;
	if (!line)
		return (false);
	splited = ft_split(line, 0, 0);
	for (i = 0; splited[i]; i++)
	{
		printf("[%d] :%s\n", i, splited[i]);
	}
	return (true);
}
