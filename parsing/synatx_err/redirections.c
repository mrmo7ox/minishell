/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:19:38 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/02 10:54:15 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	validate_redirections(char **line)
{
	int	count;

	count = 0;
	while (**line && ft_chrstr(**line, "<>()"))
	{
		if (ft_chrstr(**line, "<>"))
			count++;
		if (count > 2)
			return (false);
		(*line)++;
	}
	while (ft_whitespaces(**line))
		(*line)++;
	if (**line && ft_chrstr(**line, "<>&|;#"))
		return (false);
	return (true);
}

static bool	process_characters(char **line)
{
	if (ft_chrstr(**line, "<>"))
	{
		if (!validate_redirections(line))
			return (false);
	}
	else
		(*line)++;
	return (true);
}

static bool	check_after(char *line)
{
	while (*line)
	{
		skip_quotes_check(&line);
		if (!*line)
			break ;
		if (!process_characters(&line))
			return (false);
	}
	return (true);
}

static bool	inthe_end(char *line)
{
	int	length;

	length = ft_strlen(line);
	if (length > 0 && ft_chrstr(line[length - 1], "<>"))
		return (false);
	return (true);
}

bool	redir_handler(char *line)
{
	if (!correct_count(line) || !correct_format(line) || !check_after(line))
		return (false);
	if (!inthe_end(line))
		return (false);
	return (true);
}
