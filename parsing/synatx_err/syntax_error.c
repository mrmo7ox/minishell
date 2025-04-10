/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:44:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/10 10:08:49 by ihamani          ###   ########.fr       */
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
	int	count;

	i = 0;
	count = 0;
	if (!qoutes(line) || !and_or(line)
		|| !parenthesis(line, &i, 0, count)
		|| !redir_handler(line))
	{	
		printf("syntax error\n");
		return (false);
	}
	return (true);
}
