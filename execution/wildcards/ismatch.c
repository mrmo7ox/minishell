/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:58:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 15:23:48 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_(t_ismatch *u)
{
	u->i = 0;
	u->j = 0;
	u->star_i = -1;
	u->star_j = -1;
}

void	skip_star(char *p, t_ismatch *u)
{
	while (p[u->j] == '*')
		(u->j)++;
}

bool	ismatch(char *s, char *p)
{
	t_ismatch	u;

	init_(&u);
	while (s[u.i])
	{
		if (p[u.j] == s[u.i])
		{
			u.i++;
			u.j++;
		}
		else if (p[u.j] == '*')
		{
			u.star_j = u.j++;
			u.star_i = u.i;
		}
		else if (u.star_j != -1)
		{
			u.j = u.star_j + 1;
			u.i = ++u.star_i;
		}
		else
			return (false);
	}
	skip_star(p, &u);
	return (p[u.j] == '\0');
}
