/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:19:44 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/02 11:52:24 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	helper(char *arg, t_qoutes **q, t_expand **d, t_e_h *h)
{
	h->type = is_dollar_in_quotes(q, *(h->j));
	h->data = is_index_on_dollar(d, *(h->j));
	if ((arg[*(h->j)] == '$' || h->data) && h->type == INSIDED)
	{
		*(h->j) = process_dollar_expansion(arg, *(h->j), h->c, &(h->line));
		return (true);
	}
	else if (is_im_quotes(q, *(h->j)))
	{
		(*(h->j))++;
		return (true);
	}
	h->line = ft_addchr(h->line, arg[*(h->j)], h->c);
	(*(h->j))++;
	return (false);
}

char	*handle_dollar_in_quotes(char *arg, t_c *c)
{
	t_list		*u;
	t_e_h		*h;
	t_expand	*dollars;
	t_qoutes	*qoutes;
	int			j;

	j = 0;
	u = ft_malloc(sizeof(t_list), c->garbage);
	h = ft_malloc(sizeof(t_e_h), c->garbage);
	qoutes = NULL;
	dollars = NULL;
	u->expand = &dollars;
	u->qoutes = &qoutes;
	u->i = 0;
	u->j = 0;
	u->line = arg;
	get_quote_index(u, c->garbage);
	get_expand_index(u, c->garbage);
	h->line = ft_strdup("", c->garbage);
	h->j = &j;
	h->c = c;
	while (arg[*(h->j)])
		helper(arg, u->qoutes, u->expand, h);
	return (h->line);
}
