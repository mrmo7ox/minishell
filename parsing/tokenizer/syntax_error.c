/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:44:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/17 13:06:18 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	qoutes(char *line)
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

static bool	parenthesis(char *line, int *i, int depth)
{
	while (line[*i])
	{
		skip_qoutes(line, i);
		if (!line[*i])
			break ;
		if (line[*i] == '(')
		{
			(*i)++;
			if (!parenthesis(line, i, depth + 1))
				return (false);
		}
		else if (line[*i] == ')')
		{
			if (depth == 0)
				return (false);
			(*i)++;
			return (true);
		}
		else
			(*i)++;
	}
	return (depth == 0);
}

bool	correct_count(char *line)
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
		if (ft_chrstr(*line, "|;&"))
			return (false);
		if (count <= 2 && !ft_chrstr(*line, "<>"))
			count = 0;
		if (count > 2 || *line == '\0')
			break;
		line++;
	}
	if (count > 2)
		return (false);
	return (true);
}

bool	correct_format(char *line)
{
	char	oldchr;

	if (!*line)
		return (true);
	while (*line)
	{
		if(ft_chrstr(*line, "<>"))
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

bool	inthe_end(char *line)
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

	if(!correct_count(line) || !correct_format(line))
		return (false);
	if(!inthe_end(line))
		return (false);
	return (true);
}

bool	syntax_error(char *line)
{
	int	i = 0;

	if (!qoutes(line) || !and_or(line) 
		|| !parenthesis(line, &i, 0) 
		|| !redir_handler(line))
		printf("syntax error\n");
	return (true);
}
