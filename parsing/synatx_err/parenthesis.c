/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:21:13 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/09 17:36:00 by ihamani          ###   ########.fr       */
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

bool	parenthesis(char *line, int *i, int depth)
{
	int	count;
	int tmp;

	count = 0;
	while (line[*i])
	{
		skip_qoutes(line, i);
		if (!line[*i])
			break ;
		if (line[*i] == '(')
		{
			if (count)
			{
				tmp = (*i) - 1;
				while (line[tmp] == ' ')
					tmp--;
				if (line[tmp] && !ft_chrstr(line[tmp], "|&<>"))
					return (false);
			}
			(*i)++;
			if (!parenthesis(line, i, depth + 1))
				return (false);
		}
		else if (line[*i] == ')')
		{
			if (depth == 0 || !count)
				return (false);
			(*i)++;
			while (line[*i] == ' ')
				(*i)++;
			if (line[*i] && !ft_chrstr(line[*i], "|&<>"))
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
