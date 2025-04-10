/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:21:13 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/10 14:34:14 by ihamani          ###   ########.fr       */
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

static bool	check_before(char *line, int i, int count)
{
	if (count)
	{
		i--;
		while (line[i] == ' ')
			i--;
		if (line[i] && !ft_chrstr(line[i], "|&<>"))
			return (false);
	}
	return (true);
}

static bool	check_after(char *line, int *i)
{
	(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] && !ft_chrstr(line[*i], "|&<>"))
		return (false);
	return (true);
}

bool	parenthesis(char *line, int *i, int depth, int count)
{
	while (line[*i])
	{
		skip_qoutes(line, i);
		skip(line, i);
		if (line[*i] == '(')
		{
			if (!check_before(line, *i, count))
				return (false);
			(*i)++;
			if (!parenthesis(line, i, depth + 1, 0))
				return (false);
		}
		else if (line[*i] == ')')
		{
			if (depth == 0 || !count || !check_after(line, i))
				return (false);
			return (true);
		}
		else
		{
			(*i)++;
			count++;
		}
	}
	return (depth == 0);
}
