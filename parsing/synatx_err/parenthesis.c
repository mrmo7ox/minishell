/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:21:13 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/29 10:06:01 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '&');
}

static void	skip_quotes(char *line, int *i)
{
	char	quote;

	if (!line || !line[*i])
		return ;
	while (line[*i] == '\'' || line[*i] == '\"')
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] == quote)
			(*i)++;
	}
}

bool	is_operator_before(char *line, int *open_count, int *j, int *i)
{
	(*j) = (*i) - 1;
	while ((*j) >= 0 && ft_whitespaces(line[(*j)]))
		(*j)--;
	if ((*j) < 0 || (!is_operator(line[(*j)]) && line[(*j)] != '('))
		return (false);
	(*open_count)++;
	return (true);
}

static bool	is_operator_after(char *line, int *open_count, int *j, int *i)
{
	(*j) = (*i) + 1;
	while (line[*j] && ft_whitespaces(line[(*j)]))
		(*j)++;
	if (line[*j] && !ft_chrstr(line[*j], "|&<>)"))
		return (false);
	(*open_count)--;
	return (true);
}

bool	parenthesis(char *line, int open_count, int i, int j)
{
	while (line[i] != '\0')
	{
		skip_quotes(line, &i);
		if (line[i] == '(')
		{
			if (i == 0)
			{
				open_count++;
				i++;
				continue ;
			}
			if (!is_operator_before(line, &open_count, &j, &i))
				return (false);
		}
		else if (line[i] == ')')
		{
			if ((open_count == 0) || (line[i - 1] == '(')
				|| !is_operator_after(line, &open_count, &j, &i))
				return (false);
		}
		move_next(line, &i);
	}
	if (open_count > 0)
		return (false);
	return (true);
}
