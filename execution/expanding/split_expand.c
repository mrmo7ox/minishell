/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:47:41 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/08 12:33:20 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_qoute_list(t_list *u, t_gc **garbage, char qoute)
{
	t_qtype	type;

	if (qoute == '\'')
		type = SQOUTE;
	else if (qoute == '\"')
		type = DQOUTE;
	else
		return ;
	ft_add_qoute(u->qoutes, ft_new_node(u->j, u->i, type, garbage));
}

void	add_to_expand_list(t_list *u, bool expand_s, t_gc **garbage)
{
	ft_add_expand(u->expand, ft_new_expand(u->j, u->i, expand_s, garbage));
}

void	get_qoute_index(t_list *u, t_gc **garbage)
{
	char	qoute;

	while (u->line[u->i])
	{
		if (ft_chrstr(u->line[u->i], "\"\'"))
		{
			u->j = u->i;
			qoute = u->line[u->i];
			u->i++;
			while (u->line[u->i] && u->line[u->i] != qoute)
				u->i++;
			if (u->line[u->i] == qoute)
			{
				add_to_qoute_list(u, garbage, qoute);
				u->i++;
			}
		}
		else
			u->i++;
	}
}

void	get_expand_index(t_list *u, t_gc **garbage)
{
	while (u->line[u->i])
	{
		if (u->line[u->i] == '$')
		{
			u->j = u->i;
			u->i++;
			if (u->line[u->i] && (ft_isdigit(u->line[u->i])
					|| ft_chrstr(u->line[u->i], "@#$?%!-_")))
			{
				add_to_expand_list(u, true, garbage);
				if (u->line[u->i] != '\0')
					u->i++;
			}
			else if (ft_isalpha(u->line[u->i]))
			{
				while (ft_isalpha(u->line[u->i]) || ft_isdigit(u->line[u->i]))
					u->i++;
				add_to_expand_list(u, true, garbage);
				if (u->line[u->i] != '\0')
					u->i++;
			}
			else
				u->i++;
		}
		else
			u->i++;
	}
}

t_list	split_expand(char *line, t_gc **garbage, t_env **ft_env)
{
	t_list		u;
	t_expand	*expand;
	t_qoutes	*qoutes;

	expand = NULL;
	qoutes = NULL;
	(void)ft_env;
	u.i = 0;
	u.j = 0;
	u.line = line;
	u.qoutes = &qoutes;
	u.expand = &expand;
	get_qoute_index(&u, garbage);
	u.i = 0;
	u.j = 0;
	// get_expand_index(&u, garbage);
	return (u);
}
