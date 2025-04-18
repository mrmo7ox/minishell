/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:06:51 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/16 10:29:32 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	mod_chrstr(char chr, char *str)
{
	while (*str != '\0')
	{
		if (chr == *str)
			return (chr);
		str++;
	}
	return (0);
}

void	skip(char *line, int *i)
{
	int	chr;

	chr = mod_chrstr(line[*i], "\"\'");
	if (chr && line[*i])
	{
		(*i)++;
		while (line[*i] && line[*i] != chr)
			(*i)++;
		if (line[*i])
			(*i)++;
	}
}
