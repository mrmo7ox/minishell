/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:14:42 by moel-oua          #+#    #+#             */
/*   Updated: 2025/05/10 11:59:17 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	calculate_new_size(char *line, t_list *utils, t_gc **garbage)
{
	t_size	size_utils;

	size_utils.i = 0;
	size_utils.new_size = 0;
	while (line[size_utils.i])
	{
		size_utils.start_end = is_index_on_dollar(utils->expand, size_utils.i);
		if (size_utils.start_end && is_dollar_in_quotes(utils->qoutes,
				size_utils.i))
		{
			size_utils.len = size_utils.start_end->end
				- size_utils.start_end->start + 1;
			size_utils.holder = ft_substr(line, size_utils.start_end->start + 1,
					size_utils.len - 1, garbage);
			size_utils.temp = ft_getenv(size_utils.holder, utils->env);
			if (size_utils.temp)
				size_utils.new_size += ft_strlen(size_utils.temp);
			size_utils.i += size_utils.len;
		}
		else if (!is_im_quotes(utils->qoutes, size_utils.i))
			size_utils.new_size++, size_utils.i++;
		else
			size_utils.i++;
	}
	return (size_utils.new_size);
}

static void	fill_new_string(char *line, char *new, t_list *utils,
		t_gc **garbage)
{
	t_new	string;

	string.i = 0;
	string.pos = 0;
	while (line[string.i])
	{
		string.start_end = is_index_on_dollar(utils->expand, string.i);
		if (string.start_end && is_dollar_in_quotes(utils->qoutes, string.i))
		{
			string.len = string.start_end->end - string.start_end->start + 1;
			string.holder = ft_substr(line, string.start_end->start + 1,
					string.len - 1, garbage);
			string.temp = ft_getenv(string.holder, utils->env);
			if (string.temp)
			{
				ft_strcpy(new + string.pos, string.temp);
				string.pos += ft_strlen(string.temp);
			}
			string.i += string.len;
		}
		else if (!is_im_quotes(utils->qoutes, string.i))
			new[string.pos++] = line[string.i++];
		else
			string.i++;
	}
	new[string.pos] = '\0';
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
	get_quote_index(&u, c->garbage);
	get_expand_index(&u, c->garbage);
	new = remove_quotes_and_expand(line, &u, c->garbage);
	return (new);
}