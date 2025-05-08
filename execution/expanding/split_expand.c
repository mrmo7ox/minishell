/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:47:41 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/08 13:12:57 by moel-oua         ###   ########.fr       */
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

t_list	get_expand_index(char *line, t_gc **garbage)
{
	t_list		y;
	t_expand	*expander;

	expander = NULL;
	y.i = 0;
	y.j = 0;
	y.line = line;
	y.expand = &expander;
	while (y.line[y.i])
	{
		if (y.line[y.i] == '$')
		{
			y.j = y.i;
			y.i++;
			if (y.line[y.i] && (ft_isdigit(y.line[y.i])
					|| ft_chrstr(y.line[y.i], "@#$?%!-_")))
			{
				add_to_expand_list(&y, true, garbage);
				if (y.line[y.i] != '\0')
					y.i++;
			}
			else if (ft_isalpha(y.line[y.i]))
			{
				while (ft_isalpha(y.line[y.i]) || ft_isdigit(y.line[y.i])
					|| y.line[y.i] == '_')
					y.i++;
				if (!ft_isalpha(y.line[y.i]) || !ft_isdigit(y.line[y.i])
					|| y.line[y.i] == '_')
				{
					y.i--;
					add_to_expand_list(&y, true, garbage);
				}
				if (y.line[y.i] != '\0')
					y.i++;
			}
			else
				y.i++;
		}
		else
			y.i++;
	}
	return (y);
}

t_list	split_expand(char *line, t_gc **garbage, t_env **ft_env)
{
	t_list		u;
	t_list		y;
	t_qoutes	*qoutes;

	qoutes = NULL;
	(void)ft_env;
	u.i = 0;
	u.j = 0;
	u.line = line;
	u.qoutes = &qoutes;
	get_qoute_index(&u, garbage);
	y = get_expand_index(line, garbage);
	y.qoutes = u.qoutes;
	return (y);
}
