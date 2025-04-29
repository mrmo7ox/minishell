/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:48:38 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/28 20:48:12 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_whitespaces(char chr)
{
	if ((chr >= 9 && chr <= 13) || (chr == ' '))
		return (true);
	return (false);
}

void	ft_skip_wspaces(char *line, int *i)
{
	while (line[*i] && ft_whitespaces(line[*i]))
		(*i)++;
}
