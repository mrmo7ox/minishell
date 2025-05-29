/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:41:44 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/29 11:34:12 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	or(char *line, int *i)
{
	if (*i == 0)
		return (false);
	(*i)++;
	if (line[*i] == '|')
		(*i)++;
	while (line[*i] && ft_chrstr(line[*i], "() "))
		(*i)++;
	if (!line[*i] || ft_chrstr(line[*i], "|&;"))
		return (false);
	return (true);
}

static bool	and(char *line, int *i)
{
	if (*i == 0)
		return (false);
	(*i)++;
	if (line[*i] != '&')
		return (false);
	else
		(*i)++;
	while (line[*i] && ft_chrstr(line[*i], "() "))
		(*i)++;
	if (!line[*i] || ft_chrstr(line[*i], "|&;"))
		return (false);
	return (true);
}

bool	and_or(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (! or (line, &i))
				return (false);
		}
		else if (line[i] == '&')
		{
			if (!and(line, &i))
				return (false);
		}
		skip(line, &i);
		if (line[i] && line[i] != '|' && line[i] != '&')
			i++;
	}
	return (true);
}
