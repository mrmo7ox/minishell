/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/09 13:45:39 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	calculate_new_size(char *line, t_list *utils, t_gc **gc)
{
	t_size	size_utils;

	size_utils.i = 0;
	size_utils.new_size = 0;
	while (line[size_utils.i])
	{
		size_utils.start_end = is_index_on_dollar(utils->expand, size_utils.i);
		if ((utils->e && size_utils.start_end) || (size_utils.start_end
				&& is_dollar_in_quotes(utils->qoutes, size_utils.i)))
		{
			size_utils.len = size_utils.start_end->end
				- size_utils.start_end->start + 1;
			size_utils.holder = ft_substr(line, size_utils.start_end->start + 1,
					size_utils.len - 1, gc);
			size_utils.temp = ft_getenv(size_utils.holder, utils->env);
			if (size_utils.temp)
				size_utils.new_size += ft_strlen(size_utils.temp);
			size_utils.i += size_utils.len;
		}
		else if (utils->r && !is_im_quotes(utils->qoutes, size_utils.i))
			size_utils.new_size++, size_utils.i++;
		else
			size_utils.i++;
	}
	return (size_utils.new_size);
}

static void	fill_new_string(char *line, char *new, t_list *u, t_gc **gc)
{
	t_new	s;

	s.i = 0;
	s.pos = 0;
	while (line[s.i])
	{
		s.start_end = is_index_on_dollar(u->expand, s.i);
		if ((u->e && s.start_end) || (s.start_end
				&& is_dollar_in_quotes(u->qoutes, s.i)))
		{
			s.len = s.start_end->end - s.start_end->start + 1;
			s.holder = ft_substr(line, s.start_end->start + 1, s.len - 1, gc);
			s.temp = ft_getenv(s.holder, u->env);
			if (s.temp)
			{
				ft_strcpy(new + s.pos, s.temp);
				s.pos += ft_strlen(s.temp);
			}
			s.i += s.len;
		}
		else if (u->r && !is_im_quotes(u->qoutes, s.i))
			new[s.pos++] = line[s.i++];
		else
			s.i++;
	}
	new[s.pos] = '\0';
}

char	*remove_quotes_and_expand(char *line, t_list *utils, t_gc **gc)
{
	char	*new;
	size_t	new_size;

	if (!line || !utils || !gc)
		return (NULL);
	new_size = calculate_new_size(line, utils, gc);
	new = ft_malloc(new_size + 1, gc);
	if (!new)
		return (NULL);
	new[0] = '\0';
	fill_new_string(line, new, utils, gc);
	return (new);
}

char	*expander(char *line, t_gc **gc, t_env **ft_env, int *o)
{
	t_list		u;
	char		*new;
	t_qoutes	*quotes;
	t_expand	*expand_res;

	new = NULL;
	quotes = NULL;
	expand_res = NULL;
	if (!line || !gc || !ft_env)
		return (NULL);
	ft_memset(&u, 0, sizeof(t_list));
	u.line = line;
	u.qoutes = &quotes;
	u.expand = &expand_res;
	u.env = ft_env;
	u.r = o[0];
	u.e = o[1];
	get_quote_index(&u, gc);
	get_expand_index(&u, gc);
	new = remove_quotes_and_expand(line, &u, gc);
	return (new);
}
