/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:19:38 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/10 10:11:24 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	correct_count(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (ft_chrstr(*line, "<>") && *line != '\0')
		{
			count++;
			line++;
		}
		if (count <= 2 && !ft_chrstr(*line, "<>"))
			count = 0;
		if (count > 2 || *line == '\0')
			break ;
		line++;
	}
	if (count > 2)
		return (false);
	return (true);
}

static bool	correct_format(char *line)
{
	char	oldchr;

	if (!*line)
		return (true);
	oldchr = 0;
	while (*line)
	{
		if (ft_chrstr(*line, "<>"))
			oldchr = *line;
		while (oldchr == *line && *line)
			line++;
		if (oldchr == '>')
		{
			if (ft_chrstr(*line, "<"))
				return (false);
		}
		else
		{
			if (ft_chrstr(*line, ">"))
				return (false);
		}	
		while (!ft_chrstr(*line, "<>") && *line)
			line++;
	}
	return (true);
}

static	bool	check_after(char *line)
{
	while (*line)
	{
		if (ft_chrstr(*line, "<>"))
		{
			while (*line && ft_chrstr(*line, "<> ()"))
				line++;
			if (*line && ft_chrstr(*line, "&|;"))
				return (false);
		}
		if (*line)
			line++;
	}
	return (true);
}

static bool	inthe_end(char *line)
{
	int	length;

	length = ft_strlen(line);
	if (length > 0 && ft_chrstr(line[length - 1], "<>"))
		return (false);
	else
		return (true);
}

bool	redir_handler(char *line)
{
	if (!correct_count(line) || !correct_format(line)
		|| !check_after(line))
		return (false);
	if (!inthe_end(line))
		return (false);
	return (true);
}
