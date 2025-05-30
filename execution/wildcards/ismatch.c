/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:58:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/30 17:08:03 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	handle_wildcard(char *s, char *p, int *i, int *j, int *star_i,
		int *star_j)
{
	if (p[*j] == '*')
	{
		*star_j = *j;
		(*j)++;
		*star_i = *i;
		return (true);
	}
	else if (*star_j != -1)
	{
		*j = *star_j + 1;
		*i = ++(*star_i);
		return (true);
	}
	return (false);
}

bool	ismatch(char *s, char *p)
{
	int	i;
	int	j;
	int	star_i;
	int	star_j;

	i = 0;
	j = 0;
	star_i = -1;
	star_j = -1;
	while (s[i])
	{
		if (p[j] == s[i])
		{
			i++;
			j++;
		}
		else if (!handle_wildcard(s, p, &i, &j, &star_i, &star_j))
		{
			return (false);
		}
	}
	while (p[j] == '*')
		j++;
	return (p[j] == '\0');
}
