/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:12:30 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/10 10:44:08 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	spc(char *line, int *i)
{
	while (ft_chrstr(line[*i], "<>|&(\"'") && line[*i] != '\0')
	{
		if (line[*i] == '(')
		{
			(*i)++;
			while (line[*i] != '\0' && line[*i] != ')')
				(*i)++;
		}
		else if (line[*i] == '\'')
		{
			(*i)++;
			while (line[*i] != '\0' && line[*i] != '\'')
				(*i)++;
		}
		else if (line[*i] == '"')
		{
			(*i)++;
			while (line[*i] != '\0' && line[*i] != '"')
				(*i)++;
		}
		(*i)++;
	}
}

void	strlen_spc(char *line, int *i)
{
	if (line[*i] == '(')
	{
		(*i)++;
		while (line[*i] != '\0' && line[*i] != ')')
			(*i)++;
		(*i)++;
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		(*i)++;
		while (line[*i] != '\0' && line[*i] != '\'')
			(*i)++;
		(*i)++;
	}
	else if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] != '\0' && line[*i] != '"')
			(*i)++;
		(*i)++;
	}
	else
		(*i)++;
}
