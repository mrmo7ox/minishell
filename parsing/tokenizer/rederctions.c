/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederctions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:28:57 by ihamani           #+#    #+#             */
/*   Updated: 2025/04/14 13:04:18 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_redr	*new_node(char *file_name, char *type, int here_doc, t_gc **garbage)
{
	t_redr	*new;

	new = (t_redr *)ft_malloc(sizeof(t_redr), garbage);
	new->file_name = file_name;
	new->type = type;
	new->here_doc = here_doc;
	new->next = NULL;
	return (new);
}

static void	add_redr(t_redr **head, t_redr *new)
{
	t_redr	*tmp;

	if (!head || !new)
		return ;
	tmp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_redr	*red_node(char *line, int *i, int *j, char c, t_gc **gg)
{
	if (line[*i] == c)
	{
		(*i)++;
		ft_skip_wspaces(line, i);
		*j = *i;
		while (line [*j] && !ft_whitespaces(line[*j]))
			(*j)++;
		if (c == '<')
			return (new_node(ft_substr(line, *i, (*j - *i), gg), NULL, 1, gg));
		else if (c == '>')
			return (new_node(ft_substr(line, *i, (*j - *i), gg), "ap", 0, gg));
	}
	else
	{
		ft_skip_wspaces(line, i);
		*j = *i;
		while (line [*j] && !ft_whitespaces(line[*j]))
			(*j)++;
		if (c == '<')
			return (new_node(ft_substr(line, *i, (*j - *i), gg), "in", 0, gg));
		else
			return (new_node(ft_substr(line, *i, (*j - *i), gg), "out", 0, gg));
	}
	return (NULL);
}

void	rederction(char *line, t_redr **redr, t_gc **gg)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (line[i])
	{
		c = mod_chrstr(line[i], "<>");
		if (c)
		{
			i++;
			add_redr(redr, red_node(line, &i, &j, c, gg));
		}
		i++;
	}
}
