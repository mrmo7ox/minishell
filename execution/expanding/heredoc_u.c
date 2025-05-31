/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:40:06 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/31 15:47:13 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	cases(char *holder)
{
	if ((!ft_strcmp(holder, "'") || !ft_strcmp(holder, "\"")))
		return (true);
	else
		return (false);
}

bool	find_case(t_new *s, char *new, char *line, t_list *utils)
{
	if (cases(s->holder))
	{
		new[s->pos++] = line[s->i++];
		return (false);
	}
	if (!ft_strcmp(s->holder, "?"))
		s->temp = ft_itoa(utils->status, utils->garbage);
	else
		s->temp = ft_getenv(s->holder, utils->env);
	if (s->temp)
	{
		ft_strcpy(new + s->pos, s->temp);
		s->pos += ft_strlen(s->temp);
	}
	return (true);
}

bool	find_case_b(t_size *u, t_list *utils)
{
	if (cases(u->holder))
	{
		u->new_size++;
		u->i++;
		return (false);
	}
	if (!ft_strcmp(u->holder, "?"))
		u->temp = ft_itoa(utils->status, utils->garbage);
	else
		u->temp = ft_getenv(u->holder, utils->env);
	if (u->temp)
		u->new_size += ft_strlen(u->temp);
	return (true);
}
