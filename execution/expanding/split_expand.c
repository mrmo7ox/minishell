/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:47:41 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/05 18:11:47 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_res(t_expander *u, t_gc **garbage, bool expand_it)
{
	char	*new;

	if (u->start < u->i)
	{
		new = ft_copy(u->line + u->start, u->i - u->start, garbage);
		if (expand_it)
		{
			new = ft_getenv(ft_strip('$', new, garbage), u->env);
		}
		u->result = ft_strjoin(u->result, new, garbage);
		u->start = u->i;
	}
}

void	handle_expandable(t_expander *u, t_gc **garbage, bool from_double)
{
	add_to_res(u, garbage, false);
	if (u->line[u->i] == '$')
	{
		u->start = u->i;
		u->i++;
		if (u->line[u->i] == '\0' || u->line[u->i] == ' '
			|| u->line[u->i] == '"' || u->line[u->i] == '\'')
		{
			add_to_res(u, garbage, false);
		}
		else if (ft_isdigit(u->line[u->i]))
		{
			u->i++;
			add_to_res(u, garbage, true);
		}
		else if (ft_isalpha(u->line[u->i]) || u->line[u->i] == '_')
		{
			while (ft_isalnum(u->line[u->i]) || u->line[u->i] == '_')
				u->i++;
			add_to_res(u, garbage, true);
		}
		else
		{
			if (ft_chrstr(u->line[u->i], "@#$?%!-_"))
			{
				u->i++;
				add_to_res(u, garbage, true);
				return ;
			}
			u->i++;
			add_to_res(u, garbage, false);
		}
	}
}
void	handle_double_quote(t_expander *u, t_gc **garbage)
{
	add_to_res(u, garbage, false);
	if (u->line[u->i] == '"')
	{
		u->start = u->i;
		u->i++;
		while (u->line[u->i] && u->line[u->i] != '"')
		{
			if (u->line[u->i] == '$')
				handle_expandable(u, garbage, true);
			else
				u->i++;
		}
		if (u->line[u->i] == '"')
			u->i++;
		add_to_res(u, garbage, false);
	}
}

void	handle_single_quote(t_expander *u, t_gc **garbage)
{
	add_to_res(u, garbage, false);
	if (u->line[u->i] == '\'')
	{
		u->start = u->i;
		u->i++;
		while (u->line[u->i] && u->line[u->i] != '\'')
			u->i++;
		if (u->line[u->i] == '\'')
			u->i++;
		add_to_res(u, garbage, false);
	}
}

void	handle_word(t_expander *u, t_gc **garbage)
{
	add_to_res(u, garbage, false);
	if (u->line[u->i] && !ft_chrstr(u->line[u->i], "$'\""))
	{
		u->start = u->i;
		while (u->line[u->i] && !ft_chrstr(u->line[u->i], "$'\""))
			u->i++;
		add_to_res(u, garbage, false);
	}
}

void	loop_and_replace(t_expander *u, t_gc **garbage)
{
	while (u->line[u->i])
	{
		if (u->line[u->i] == '"')
			handle_double_quote(u, garbage);
		else if (u->line[u->i] == '\'')
			handle_single_quote(u, garbage);
		else if (u->line[u->i] == '$')
			handle_expandable(u, garbage, false);
		else
			handle_word(u, garbage);
	}
}

t_expander	split_expand(char *line, t_gc **garbage, t_env **ft_env)
{
	t_expander	u;

	u.i = 0;
	u.env = 0;
	u.start = 0;
	u.result = NULL;
	u.line = line;
	u.env = ft_env;
	if (!line)
		return (u);
	loop_and_replace(&u, garbage);
	return (u);
}
