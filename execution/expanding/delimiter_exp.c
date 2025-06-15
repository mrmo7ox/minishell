/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:35:09 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/15 10:27:59 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	d_case(char *line, int *i, char **new, t_c *c)
{
	char	qoute;

	if (line[(*i) + 1] && ft_chrstr(line[(*i) + 1], "\"\'"))
	{
		(*i)++;
		qoute = line[(*i)++];
		while (line[(*i)] && line[(*i)] != qoute)
		{
			*new = ft_addchr(*new, line[(*i)++], c);
		}
		if (qoute == line[(*i)])
			(*i)++;
		return (true);
	}
	else if (line[(*i) + 1] && ft_chrstr(line[(*i) + 1], "$"))
	{
		*new = ft_strjoin(*new, "$$", c->garbage);
		(*i) += 2;
		return (true);
	}
	else
	{
		*new = ft_addchr(*new, line[(*i)++], c);
		return (true);
	}
}

bool	q_case(char *line, int *i, char **new, t_c *c)
{
	char	qoute;

	qoute = line[(*i)];
	(*i)++;
	while (line[(*i)] && line[(*i)] != qoute)
	{
		*new = ft_addchr(*new, line[(*i)], c);
		(*i)++;
	}
	if (qoute == line[(*i)])
		(*i)++;
	return (true);
}

char	*del_exp(char *line, t_c *c)
{
	int		i;
	char	*new;

	new = ft_strdup("", c->garbage);
	if (!line)
		return (ft_strdup("", c->garbage));
	i = 0;
	while (line[i])
	{
		if (ft_chrstr(line[i], "$"))
		{
			if (d_case(line, &i, &new, c))
				continue ;
		}
		else if (ft_chrstr(line[i], "\"\'"))
		{
			if (q_case(line, &i, &new, c))
				continue ;
		}
		new = ft_addchr(new, line[i], c);
		i++;
	}
	return (new);
}
