/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:40:06 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/01 17:54:33 by ihamani          ###   ########.fr       */
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

char	**convert_to_array(t_arg **head, t_c *c)
{
	char	**new;

	new = ft_malloc(sizeof(char *) * (ft_args_size(*head) + 1), c->garbage);
	if (!new)
		return (NULL);
	convert(head, new);
	return (new);
}

t_list	*init_list(char *arg, t_c *c)
{
	t_list		*u;
	t_expand	*dollars;
	t_qoutes	*qoutes;

	u = ft_malloc(sizeof(t_list), c->garbage);
	qoutes = NULL;
	dollars = NULL;
	u->expand = &dollars;
	u->qoutes = &qoutes;
	u->i = 0;
	u->j = 0;
	u->line = arg;
	get_quote_index(u, c->garbage);
	get_expand_index(u, c->garbage);
	return (u);
}
