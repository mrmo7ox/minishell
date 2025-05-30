/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redire_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:50:48 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/29 09:51:57 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_double_quote(char **line)
{
	(*line)++;
	while (**line && **line != '"')
		(*line)++;
	if (**line == '"')
		(*line)++;
}

void	skip_single_quote(char **line)
{
	(*line)++;
	while (**line && **line != '\'')
		(*line)++;
	if (**line == '\'')
		(*line)++;
}

void	skip_quotes_check(char **line)
{
	if (**line == '"')
		skip_double_quote(line);
	else if (**line == '\'')
		skip_single_quote(line);
}

void	update_count_and_check(char **line, int *count)
{
	while (ft_chrstr(**line, "<>") && **line != '\0')
	{
		(*count)++;
		(*line)++;
	}
}

bool	check_count_validity(int count, char *line)
{
	if (count <= 2 && !ft_chrstr(*line, "<>"))
		return (true);
	if (count > 2 || *line == '\0')
		return (false);
	return (true);
}
