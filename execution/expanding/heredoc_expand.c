/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:43:50 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/14 15:30:20 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	calculate_new_size(char *line, t_list *utils, t_gc **garbage)
{
	t_size	u;

	u.i = 0;
	u.new_size = 0;
	while (line[u.i])
	{
		u.start_end = is_index_on_dollar(utils->expand, u.i);
		if (u.start_end)
		{
			u.len = u.start_end->end - u.start_end->start + 1;
			u.holder = ft_substr(line, u.start_end->start + 1, u.len - 1,
					garbage);
			find_case_b(&u, utils);
			u.i += u.len;
		}
		else
		{
			u.new_size++;
			u.i++;
		}
	}
	return (u.new_size);
}

static void	fill_new_string(char *line, char *new, t_list *utils,
		t_gc **garbage)
{
	t_new	s;

	s.i = 0;
	s.pos = 0;
	while (line[s.i])
	{
		s.start_end = is_index_on_dollar(utils->expand, s.i);
		if (s.start_end)
		{
			s.len = s.start_end->end - s.start_end->start + 1;
			s.holder = ft_substr(line, s.start_end->start + 1, s.len - 1,
					garbage);
			if (!find_case(&s, new, line, utils))
				continue ;
			s.i += s.len;
		}
		else
			new[s.pos++] = line[s.i++];
	}
	new[s.pos] = '\0';
}

char	*expand_only(char *line, t_list *utils, t_gc **garbage)
{
	char	*new;
	size_t	new_size;

	if (!line || !utils || !garbage)
		return (NULL);
	new_size = calculate_new_size(line, utils, garbage);
	new = ft_malloc(new_size + 1, garbage);
	if (!new)
		return (NULL);
	fill_new_string(line, new, utils, garbage);
	if (!new || !*new)
		return (ft_strdup("", garbage));
	return (new);
}

char	*h_expander(char *line, t_c *c)
{
	t_list		u;
	char		*new;
	t_qoutes	*quotes;
	t_expand	*expand_res;

	new = NULL;
	quotes = NULL;
	expand_res = NULL;
	if (!line || !c->garbage || !c->ft_env)
		return (NULL);
	ft_memset(&u, 0, sizeof(t_list));
	u.line = line;
	u.qoutes = &quotes;
	u.expand = &expand_res;
	u.env = c->ft_env;
	u.garbage = c->garbage;
	u.c = c;
	u.status = set_status(c->status, 0);
	get_quote_index(&u, c->garbage);
	get_expand_index(&u, c->garbage);
	new = expand_only(line, &u, c->garbage);
	return (new);
}
