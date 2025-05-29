/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:44:49 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/28 09:34:35 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*formating(char *line, t_gc **gg)
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
		line = ft_substr(line, start, (end - start) + 1, gg);
		if (!line)
		{
			ft_putstr_fd("[KO] Malloc Failed\n", 2);
			return (NULL);
		}
	}
	return (line);
}

bool	syntax_error(char *line)
{
	if (!qoutes(line) || !and_or(line) || !parenthesis(line, 0, 0, 0)
		|| !redir_handler(line))
	{
		ft_putstr_fd("Syntax error\n", 2);
		set_status(2, -1);
		return (false);
	}
	return (true);
}
