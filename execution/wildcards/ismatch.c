/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:58:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/29 21:24:06 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	match_or_backtrack(char *s, char *p, int *i, int *j)
{
	static int	najma_index = -1;
	static int	matchindex = -1;

	if (p[*j] == '*')
	{
		najma_index = *j;
		matchindex = *i;
		(*j)++;
		return (true);
	}
	else if (najma_index != -1)
	{
		*j = najma_index + 1;
		*i = matchindex + 1;
		matchindex = *i;
		return (true);
	}
	return (false);
}

bool	ismatch(char *s, char *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (p[j] == s[i])
		{
			i++;
			j++;
		}
		else if (!match_or_backtrack(s, p, &i, &j))
			return (false);
	}
	while (p[j] == '*')
		j++;
	return (p[j] == '\0');
}
