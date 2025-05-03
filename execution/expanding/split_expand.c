/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:47:41 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/03 10:21:11 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (!ft_isalpha(line[pos + 1]) && line[pos + 1] != '_')
		return (0);
	return (1);
}

void	handle_single_quote(char *line, t_expander *u, t_part **head, t_gc **g)
{
	int	start;

	start = u->i++;
	while (line[u->i] && line[u->i] != '\'')
		u->i++;
	u->i++;
	ft_add_part(head, ft_new_part(line, start, u->i - start, g));
}

void	handle_double_quote(char *line, t_expander *u, t_part **head, t_gc **g)
{
	int	start;

	start = u->i++;
	while (line[u->i] && line[u->i] != '"')
	{
		if (line[u->i] == '$')
		{
			if (u->i > start)
				ft_add_part(head, ft_new_part(line, start, u->i - start, g));
			start = u->i++;
			while (ft_isalnum(line[u->i]) || line[u->i] == '_')
				u->i++;
			ft_add_part(head, ft_new_part(line, start, u->i - start, g));
			start = u->i;
		}
		else
			u->i++;
	}
	u->i++;
	if (u->i > start)
		ft_add_part(head, ft_new_part(line, start, u->i - start, g));
}

void	handle_expandable(char *line, t_expander *u, t_part **head, t_gc **g,
		int start)
{
	if (u->i > start)
		ft_add_part(head, ft_new_part(line, start, u->i - start, g));
	start = u->i++;
	while (ft_isalnum(line[u->i]) || line[u->i] == '_')
		u->i++;
	ft_add_part(head, ft_new_part(line, start, u->i - start, g));
}

void	handle_literal(char *line, t_expander *u, t_part **head, t_gc **g,
		int start)
{
	while (line[u->i] && line[u->i] != '$' && line[u->i] != '"'
		&& line[u->i] != '\'')
		u->i++;
	if (u->i > start)
		ft_add_part(head, ft_new_part(line, start, u->i - start, g));
}

void	handle_parts(char *line, t_expander *u, t_part **head, t_gc **g)
{
	int	start;

	start = u->i;
	if (line[u->i] == '\'')
		handle_single_quote(line, u, head, g);
	else if (line[u->i] == '"')
		handle_double_quote(line, u, head, g);
	else if (line[u->i] == '$')
		handle_expandable(line, u, head, g, start);
	else
		handle_literal(line, u, head, g, start);
}

t_expander	split_expand(char *line, t_gc **garbage)
{
	t_expander u;
	u.i = 0;
	u.result = NULL;
	t_part *head = NULL;

	while (line[u.i])
		handle_parts(line, &u, &head, garbage);
	u.result = head;
	return (u);
}