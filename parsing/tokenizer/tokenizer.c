/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:41:20 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/14 16:55:31 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	tokenizer(t_gc **garbage, t_tk **tokens, char *line)
{
	char	**splited;
	int		i;
	char	*sap;

	(void)tokens;
	if (!line)
		return (false);
	sap = "<&>|";
	splited = ft_split(line, sap, 0, 0);
	if (!splited)
		return (false);
	add_split_gc(garbage , splited);
	i = 0;
	while (splited[i])
	{
		printf("%s\n", splited[i]);
		i++;
	}
	return (true);
}
