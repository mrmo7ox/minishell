/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:47:41 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/25 13:18:10 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_expand_list(t_list *u, bool expand_s, t_gc **garbage)
{
	t_expand	*new_expand;

	if (!u || !garbage)
		return ;
	new_expand = ft_new_expand(u->j, u->i, expand_s, garbage);
	if (!new_expand)
		return ;
	ft_add_expand(u->expand, new_expand);
}

static void	handle_simple_dollar_cases(t_list *u, t_gc **garbage)
{
	if (u->line[u->i] && (ft_isdigit(u->line[u->i]) || ft_chrstr(u->line[u->i],
				"\"'@#i!-_?")))
	{
		add_to_expand_list(u, true, garbage);
		if (u->line[u->i] != '\0')
			u->i++;
	}
}

static void	handle_named_variable(t_list *u, t_gc **garbage)
{
	if (ft_isalpha(u->line[u->i]))
	{
		while (u->line[u->i] && (ft_isalpha(u->line[u->i])
				|| ft_isdigit(u->line[u->i]) || u->line[u->i] == '_'))
		{
			u->i++;
		}
		u->i--;
		add_to_expand_list(u, true, garbage);
		if (u->line[u->i] != '\0')
			u->i++;
	}
}

static void	process_dollar_sign(t_list *u, t_gc **garbage)
{
	if (u->line[u->i] == '$')
	{
		u->j = u->i;
		u->i++;
		handle_simple_dollar_cases(u, garbage);
		handle_named_variable(u, garbage);
	}
	else
		u->i++;
}

t_list	*get_expand_index(t_list *u, t_gc **garbage)
{
	if (!u || !u->line || !garbage)
		return (u);
	u->i = 0;
	while (u->line[u->i])
		process_dollar_sign(u, garbage);
	return (u);
}
