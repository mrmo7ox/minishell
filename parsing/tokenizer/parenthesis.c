/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:21:13 by moel-oua          #+#    #+#             */
/*   Updated: 2025/03/17 13:21:47 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	parenthesis(char *line, int *i, int depth)
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
