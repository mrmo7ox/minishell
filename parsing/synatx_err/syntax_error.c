/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:44:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/09 16:30:11 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*formating(char *line)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(line) - 1;
	while (ft_whitespaces(line[start]) && (line[start] != '\0'))
		start++;
	while (end > 0 && ft_whitespaces(line[end]) && (line[end] != '\0'))
		end--;
	if (start <= end)
	{
		line = ft_substr(line, start, (end - start) + 1);
		if (!line)
		{
			printf("[KO] Malloc Failed\n");
			return (NULL);
		}
	}
	return (line);
}

bool	syntax_error(char *line)
{
	int	i;

	i = 0;
	if (!qoutes(line) || !and_or(line)
		|| !parenthesis(line, &i, 0)
		|| !redir_handler(line))
	{	
		printf("syntax error\n");
		return (false);
	}
	return (true);
}
