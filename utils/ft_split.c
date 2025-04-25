/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:05:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/04/25 11:01:36 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *ft_copy(char *src, int len)
{
	char *dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	for (int i = 0; i < len; i++)
		dup[i] = src[i];

	dup[len] = '\0';
	return (dup);
}

e_type special_cases(char *str)
{

	if (str && ft_strstr(str, "||"))
		return (OPERATOR);
	else if (str && ft_strstr(str, "&&"))
		return (OPERATOR);
	else if (str && ft_strstr(str, "|"))
		return (OPERATOR);
	return (COMMAND);
}

void ft_split(t_tk **res, t_gc **garbage, char *line, int i, int j)
{
	int priority = 0;
	int index = 0;

	while (line[i])
	{
		while (line[i] && ft_chrstr(line[i], " \t"))
			i++;
		j = i;

		if (ft_chrstr(line[i], "|&()"))
		{
			if (line[i] == '(')
			{
				priority++;
				i++;
				continue;
			}
			else if (line[i] == ')')
			{
				priority--;
				i++;
				continue;
			}
			else if ((line[i] == '|' && line[i + 1] == '|') ||
					 (line[i] == '&' && line[i + 1] == '&'))
			{
				i += 2;
			}
			else
				i += 1;

			char *token = ft_copy(&line[j], i - j);
			if (!token)
				return;
			ft_add_tk(res, ft_new_tk_node(token, priority, garbage, index++, special_cases(token)));
			continue;
		}
		while (line[i] && !ft_chrstr(line[i], "|&()\t"))
			i++;

		if (i > j)
		{
			char *token = ft_copy(&line[j], i - j);
			if (!token)
				return;
			ft_add_tk(res, ft_new_tk_node(token, priority, garbage, index++, special_cases(token)));
		}
	}
}
