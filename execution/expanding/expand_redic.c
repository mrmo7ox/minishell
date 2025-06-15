/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:30:46 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/15 10:10:35 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_both_q_and_d(char *arg, t_c *c)
{
	char	**splited;
	int		j;
	char	*new;

	j = 0;
	new = NULL;
	splited = ft_expand_split(arg, c, 0, 0);
	splited = hundler(splited, c, 0);
	if (!splited)
		return (NULL);
	while (splited[j])
	{
		new = ft_strjoin(new, splited[j], c->garbage);
		j++;
	}
	return (new);
}

char	*remove_q_redic(char *arg, t_c *c)
{
	arg = remove_qoutes(arg, c);
	if (!arg || !*arg)
		return (ft_strdup("", c->garbage));
	else
		return (arg);
}

char	*redc_expander(char *line, t_c *c)
{
	if (has_qoute(line) && !has_dollar(line))
		line = remove_q_redic(line, c);
	else if (!has_qoute(line) && has_dollar(line))
		line = expand(line, NULL, c);
	else if (has_qoute(line) && has_dollar(line))
		line = handle_both_q_and_d(line, c);
	return (line);
}
