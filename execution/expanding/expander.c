/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/10 14:31:44 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	cases(char *holder, t_dollar mode, int i)
{
	// if (mode == INSIDED)
	// {
	// 	printf("[INSIDED][%d]\n", i);
	// }
	// else if (mode == INSIDES)
	// {
	// 	printf("[INSIDES][%d]\n", i);
	// }
	// else if (mode == OUTSIDE)
	// {
	// 	printf("[OUTSIDE][%d]\n", i);
	// }
	if ((!ft_strcmp(holder, "'") || !ft_strcmp(holder, "\""))
				&& mode == INSIDED)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

static size_t	calculate_new_size(char *line, t_list *utils, t_gc **garbage)
{
	t_size	u;

	u.i = 0;
	u.new_size = 0;
	while (line[u.i])
	{
		u.start_end = is_index_on_dollar(utils->expand, u.i);
		if (u.start_end && (is_dollar_in_quotes(utils->qoutes, u.i) == OUTSIDE
				|| is_dollar_in_quotes(utils->qoutes, u.i) == INSIDED))
		{
			u.len = u.start_end->end - u.start_end->start + 1;
			u.holder = ft_substr(line, u.start_end->start + 1, u.len - 1,
					garbage);
			if (cases(u.holder, is_dollar_in_quotes(utils->qoutes, u.i), u.i))
			{
				u.new_size++, u.i++;
				continue ;
			}
			if (!ft_strcmp(u.holder, "?"))
				u.temp = ft_itoa(utils->status, garbage);
			else
				u.temp = ft_getenv(u.holder, utils->env);
			if (u.temp)
				u.new_size += ft_strlen(u.temp);
			u.i += u.len;
		}
		else if (!is_im_quotes(utils->qoutes, u.i))
			u.new_size++, u.i++;
		else
			u.i++;
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
		if (s.start_end && (is_dollar_in_quotes(utils->qoutes, s.i) == OUTSIDE
				|| is_dollar_in_quotes(utils->qoutes, s.i) == INSIDED))
		{
			s.len = s.start_end->end - s.start_end->start + 1;
			s.holder = ft_substr(line, s.start_end->start + 1, s.len - 1,
					garbage);
			if (cases(s.holder, is_dollar_in_quotes(utils->qoutes, s.i), s.i))
			{
				new[s.pos++] = line[s.i++];
				continue ;
			}
			if (!ft_strcmp(s.holder, "?"))
				s.temp = ft_itoa(utils->status, garbage);
			else
				s.temp = ft_getenv(s.holder, utils->env);
			if (s.temp)
			{
				ft_strcpy(new + s.pos, s.temp);
				s.pos += ft_strlen(s.temp);
			}
			s.i += s.len;
		}
		else if (!is_im_quotes(utils->qoutes, s.i))
			new[s.pos++] = line[s.i++];
		else
			s.i++;
	}
	new[s.pos] = '\0';
}

char	*remove_quotes_and_expand(char *line, t_list *utils, t_gc **garbage)
{
	char	*new;
	size_t	new_size;

	if (!line || !utils || !garbage)
		return (NULL);
	new_size = calculate_new_size(line, utils, garbage);
	new = ft_malloc(new_size + 1, garbage);
	if (!new)
		return (NULL);
	new[0] = '\0';
	fill_new_string(line, new, utils, garbage);
	return (new);
}

char	*expander(char *line, t_container *c)
{
	t_list u;
	char *new;
	t_qoutes *quotes;
	t_expand *expand_res;

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
	u.status = c->status;
	get_quote_index(&u, c->garbage);
	get_expand_index(&u, c->garbage);
	// t_expand *tmp = *u.expand;
	// while (tmp)
	// {
	// 	printf("[%d][%d]\n", tmp->start, tmp->end);
	// 	tmp = tmp->next;
	// }
	new = remove_quotes_and_expand(line, &u, c->garbage);
	return (new);
}