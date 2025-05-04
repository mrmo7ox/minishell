/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:47:41 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/04 10:12:19 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_expandable(t_expander *u, t_gc **g)
{
	if (u->i > u->start)
		ft_add_part(&(u->head), ft_new_part(u->line, u->start, u->i - u->start,
				g));
	u->start = u->i++;
	if (ft_isalnum(u->line[u->i]) || !ft_isalpha(u->line[u->i])
		|| u->line[u->i] == '_')
		u->i++;
	else
	{
		while (ft_isalpha(u->line[u->i]) || ft_isalnum(u->line[u->i])
			|| u->line[u->i] == '_')
			u->i++;
	}
	ft_add_part(&(u->head), ft_new_part(u->line, u->start, u->i - u->start, g));
}

void	handle_word(t_expander *u, t_gc **g)
{
	while (u->line[u->i] && u->line[u->i] != '$' && u->line[u->i] != '"'
		&& u->line[u->i] != '\'')
		u->i++;
	if (u->i > u->start)
		ft_add_part(&(u->head), ft_new_part((u->line), u->start, u->i
				- u->start, g));
}

void	handle_parts(t_expander *u, t_gc **g)
{
	u->start = u->i;
	if (u->line[u->i] == '\'')
		handle_single_quote(u, g);
	else if (u->line[u->i] == '"')
		handle_double_quote(u, g);
	else if (u->line[u->i] == '$')
		handle_expandable(u, g);
	else
		handle_word(u, g);
}

t_expander	split_expand(char *line, t_gc **garbage)
{
	t_expander	u;

	u.i = 0;
	u.result = NULL;
	u.line = line;
	u.head = NULL;
	while (line[u.i])
		handle_parts(&u, garbage);
	u.result = u.head;
	return (u);
}
