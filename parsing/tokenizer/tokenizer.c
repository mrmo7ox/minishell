/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/10 10:46:37 by ihamani          ###   ########.fr       */
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
