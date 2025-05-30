/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redire_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:52:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/29 09:53:15 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	correct_count(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == '"')
		{
			skip_double_quote(&line);
			continue ;
		}
		if (*line == '\'')
		{
			skip_single_quote(&line);
			continue ;
		}
		update_count_and_check(&line, &count);
		if (!check_count_validity(count, line))
			break ;
		if (!ft_chrstr(*line, "<>"))
			count = 0;
		if (*line)
			line++;
	}
	return (count <= 2);
}

bool	check_op_conflict(char **line, char oldchr)
{
	if (oldchr == '>')
		return (!ft_chrstr(**line, "<"));
	else
		return (!ft_chrstr(**line, ">"));
}

bool	correct_format(char *line)
{
	char	oldchr;

	oldchr = 0;
	while (*line)
	{
		if (*line == '"' || *line == '\'')
		{
			skip_quotes_check(&line);
			continue ;
		}
		if (ft_chrstr(*line, "<>"))
			oldchr = *line;
		while (*line == oldchr && *line)
			line++;
		if (!check_op_conflict(&line, oldchr))
			return (false);
		while (!ft_chrstr(*line, "<>") && *line)
			line++;
	}
	return (true);
}
