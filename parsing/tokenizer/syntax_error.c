/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:44:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/16 15:28:25 by moel-oua         ###   ########.fr       */
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

int	checke_bf(char *line ,int *i)
{
	bool	after;
	bool	before;
	int		init;
	int		count;

	after = false;
	before = false;
	init = *i;
	count = 0;
	// checking before
	while(line[*i] == '<' && line[*i])
		(count++, (*i)++);
	if(count == 0)
	{
		while(line[*i] == '>' && line[*i])
			(count++, (*i)++);
	}
	if( count != 0 && (line[*i] == '>' || line[*i] == '<') )
		return (false);
	while(line[*i] && *i > 1 && count <= 2)
	{
		if (line[*i] != ' ' && !ft_chrstr(line[*i], "<>"))
		{
			before = true;
			break;
		}
		(*i)--;
	}
	// checking before
	*i = init;
	if (count <= 2 && *i == 0)
		before = true;
	while((line[*i] == '<' || line[*i] == '>') && line[*i] != '\0')
	{
		(*i)++;
	}
	while(line[*i] && before)
	{
		if(line[*i] != ' ' && !ft_chrstr(line[*i], "<>"))
		{
			after = true;
			break;
		}
		(*i)++;
	}
	if(before && after)
	{

		return (*i);
	}
	return (false);
}

bool	redir_handler(char *line)
{
	int	i;

	i = 0;
	while (*line == ' ')
		line++;
	
	while (line[i])
	{
		if (ft_chrstr(line[i], "<>"))
		{
			if (!checke_bf(line ,&i))
				return (false);
			else
			{
				while((line[i] == '<' || line[i] == '>') && line[i] != '\0')
					(i)++;
				continue;
			}
		}
		i++;	
	}
	return (true);
}

bool	syntax_error(char *line)
{
	int	i = 0;

	if (!qoutes(line) || !and_or(line) || !parenthesis(line, &i, 0) || !redir_handler(line))
		printf("syntax error\n");
	return (true);
}
