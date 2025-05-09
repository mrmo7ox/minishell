/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/09 09:55:03 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_quote_list(t_list *u, t_gc **garbage, char quote)
{
	t_qtype		type;
	t_qoutes	*new_node;

	if (!u || !garbage)
		return ;
	if (quote == '\'')
		type = SQOUTE;
	else if (quote == '\"')
		type = DQOUTE;
	else
		return ;
	new_node = ft_new_node(u->j, u->i, type, garbage);
	if (!new_node)
		return ;
	ft_add_qoute(u->qoutes, new_node);
}

void	get_quote_index(t_list *u, t_gc **garbage)
{
	char	quote;

	if (!u || !u->line || !garbage)
		return ;
	u->i = 0;
	while (u->line[u->i])
	{
		if (ft_chrstr(u->line[u->i], "\"\'"))
		{
			u->j = u->i;
			quote = u->line[u->i];
			u->i++;
			while (u->line[u->i] && u->line[u->i] != quote)
				u->i++;
			if (u->line[u->i] == quote)
			{
				add_to_quote_list(u, garbage, quote);
				u->i++;
			}
		}
		else
			u->i++;
	}
}
