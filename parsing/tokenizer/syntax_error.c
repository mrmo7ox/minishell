/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:44:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/15 15:41:27 by moel-oua         ###   ########.fr       */
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

static bool	parenthesis(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
		{
			while (line[i] != ')' && line[i])
				i++;
			if (line[i] != ')')
				return (false);
			else
				i++;
		}
		if (line[i] == ')')
			return (false);
		i++;
	}
	return (true);
}

bool	syntax_error(char *line)
{
	if (!qoutes(line))
		printf("syntax error\n");
	if (!parenthesis(line))
		printf("syntax error\n");
	return (true);
}
