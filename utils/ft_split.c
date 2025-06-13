/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-oua <moel-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:05:01 by moel-oua          #+#    #+#             */
/*   Updated: 2025/06/02 10:58:41 by moel-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] && ft_whitespaces(line[*i]))
		(*i)++;
}

static int	handle_parentheses(char *line, t_split_utils *utils)
{
	if (line[utils->i] == '(')
	{
		utils->subshell++;
		(utils->i)++;
		return (1);
	}
	else if (line[utils->i] == ')')
	{
		utils->subshell--;
		(utils->i)++;
		return (1);
	}
	return (0);
}

static int	handle_operator(t_tk **res, t_gc **garbage, char *line,
		t_split_utils *utils)
{
	char	*token;

	if ((line[utils->i] == '|' && line[utils->i + 1] == '|')
		|| (line[utils->i] == '&' && line[utils->i + 1] == '&'))
		(utils->i) += 2;
	else if (line[utils->i] == '|' || line[utils->i] == '&')
		(utils->i)++;
	token = ft_copy(&line[utils->j], utils->i - utils->j, garbage);
	if (!token)
		return (0);
	(utils->index)++;
	(utils->type) = special_cases(token);
	(utils->priority) = ft_priority(token);
	ft_add_tk(res, ft_new_tk_node(token, garbage, utils));
	return (1);
}

static int	handle_word(t_tk **res, t_gc **garbage, char *line,
		t_split_utils *utils)
{
	char	*token;

	while (line[utils->i] && !ft_chrstr(line[utils->i], "|&()"))
	{
		if ((line[utils->i] == '"' || line[utils->i] == '\'')
			&& ft_skip_quates(&(utils->i), line))
			continue ;
		(utils->i)++;
	}
	if (utils->i > utils->j)
	{
		token = ft_copy(&line[utils->j], utils->i - utils->j, garbage);
		if (!token)
			return (0);
		(utils->index)++;
		(utils->type) = special_cases(token);
		(utils->priority) = ft_priority(token);
		ft_add_tk(res, ft_new_tk_node(token, garbage, utils));
	}
	return (1);
}

void	ft_split(t_tk **res, t_gc **garbage, char *line)
{
	t_split_utils	utils;

	utils.i = 0;
	utils.index = 0;
	utils.priority = 0;
	utils.subshell = 0;
	while (line[utils.i])
	{
		skip_spaces(line, &utils.i);
		utils.j = utils.i;
		if (ft_chrstr(line[utils.i], "|&()"))
		{
			if (handle_parentheses(line, &utils))
				continue ;
			if (!handle_operator(res, garbage, line, &utils))
				return ;
			continue ;
		}
		if (!handle_word(res, garbage, line, &utils))
			return ;
	}
}
