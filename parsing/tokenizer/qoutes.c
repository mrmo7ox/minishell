/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:23:16 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/17 13:23:54 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	skip_qoutes(char *line, int *i)
{
	char	quote;

	if (!line || !line[*i])
		return ;
	while ((line[*i] == '\'' || line[*i] == '"'))
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] == quote)
			(*i)++;
	}
}

bool	qoutes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' && line[i])
		{
			i++;
			while (line[i] != '"' && line[i])
				i++;
			if (line[i] != '"')
				return (false);
		}
		if (line[i] == '\'' && line[i])
		{
			i++;
			while (line[i] != '\'' && line[i])
				i++;
			if (line[i] != '\'')
				return (false);
		}
		i++;
	}
	return (true);
}
