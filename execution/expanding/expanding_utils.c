/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:56:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/04 10:46:36 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_double_quote(t_expander *u, t_gc **g)
{
	u->start = u->i++;
	while (u->line[u->i] && u->line[u->i] != '"')
	{
		if (u->line[u->i] == '$')
		{
			if (u->i > u->start)
				ft_add_part(&(u->head), ft_new_part(u->line, u->start, u->i
						- u->start, g));
			u->start = u->i++;
			while (ft_isalpha(u->line[u->i]) || ft_isalnum(u->line[u->i])
				|| u->line[u->i] == '_')
				u->i++;
			ft_add_part(&(u->head), ft_new_part(u->line, u->start, u->i
					- u->start, g));
			u->start = u->i;
		}
		else
			u->i++;
	}
	u->i++;
	if (u->i > u->start)
		ft_add_part(&(u->head), ft_new_part(u->line, u->start, u->i - u->start,
				g));
}

int	is_expandable(const char *line, int pos)
{
	int	in_single;
	int	i;

	i = pos;
	if (line[pos] != '$' || line[0] == '\'')
		return (0);
	in_single = 0;
	while (i >= 0)
	{
		if (line[i] == '\'')
			in_single = !in_single;
		else if (line[i] == '"')
			break ;
		i--;
	}
	if (in_single)
		return (0);
	return (1);
}

void	handle_single_quote(t_expander *u, t_gc **g)
{
	u->start = u->i++;
	while (u->line[u->i] && u->line[u->i] != '\'')
		u->i++;
	u->i++;
	ft_add_part(&(u->head), ft_new_part(u->line, u->start, u->i - u->start, g));
}

void	remove_double_quotes(t_part **curr, t_gc **garbage)
{
	if (ft_chrcount((*curr)->content, '\"') % 2 == 0)
	{
		(*curr)->content = ft_strip('\"', (*curr)->content, garbage);
		*curr = (*curr)->next;
		return ;
	}
	(*curr)->content = ft_strip('\"', (*curr)->content, garbage);
	*curr = (*curr)->next;
	while (*curr && !ft_chrstr('\"', (*curr)->content))
		*curr = (*curr)->next;
	if (*curr)
	{
		(*curr)->content = ft_strip('\"', (*curr)->content, garbage);
		*curr = (*curr)->next;
	}
}

void	remove_single_quotes(t_part **curr, t_gc **garbage)
{
	if (ft_chrcount((*curr)->content, '\'') % 2 == 0)
	{
		(*curr)->content = ft_strip('\'', (*curr)->content, garbage);
		*curr = (*curr)->next;
		return ;
	}
	(*curr)->content = ft_strip('\'', (*curr)->content, garbage);
	*curr = (*curr)->next;
	while (*curr && !ft_chrstr('\'', (*curr)->content))
		*curr = (*curr)->next;
	if (*curr)
	{
		(*curr)->content = ft_strip('\'', (*curr)->content, garbage);
		*curr = (*curr)->next;
	}
}
