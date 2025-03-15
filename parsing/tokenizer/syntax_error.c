/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:44:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/15 17:42:41 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static bool	qoutes(char *line)
{
	int	i;

	i = 0;
	while(line[i])
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

static void	skip_qoutes (char *line, int *i)
{
	char quote;

	if (!line || !line[*i])
		return;
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

static bool parenthesis(char *line, int *i, int depth)
{
	while (line[*i])
	{
		skip_qoutes(line, i);
		if (!line[*i])
			break;
		if (line[*i] == '(')
		{
			(*i)++;
			if (!parenthesis(line, i, depth + 1)) 
				return false;
		}
		else if (line[*i] == ')')
		{
			if (depth == 0)
				return false;
			(*i)++;
			return true;
		}
		else
			(*i)++; 
	}
	return (depth == 0);
}



bool	syntax_error(char *line)
{
	int i = 0;
	if (!qoutes(line))
		printf("syntax error\n");
	if (!parenthesis(line, &i, 0))
		printf("syntax error\n");
	return (true);
}
